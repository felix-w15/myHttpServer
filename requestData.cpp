//
// Created by wx on 2/21/21.
//

#include "requestData.h"
#include "Epoll.h"
#include <queue>
#include <deque>
#include <iostream>
#include <unistd.h>
#include <string>
#include <ctype.h>

pthread_mutex_t MutexLockGuard::lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t MimeType::lock = PTHREAD_MUTEX_INITIALIZER;
std::unordered_map<std::string, std::string> MimeType::mime;

std::string MimeType::getMime(const std::string &suffix) {
    if (mime.size() == 0)
    {
        pthread_mutex_lock(&lock);
        if (mime.size() == 0)
        {
            mime[".html"] = "text/html";
            mime[".avi"] = "video/x-msvideo";
            mime[".bmp"] = "image/bmp";
            mime[".c"] = "text/plain";
            mime[".doc"] = "application/msword";
            mime[".gif"] = "image/gif";
            mime[".gz"] = "application/x-gzip";
            mime[".htm"] = "text/html";
            mime[".ico"] = "application/x-ico";
            mime[".jpg"] = "image/jpeg";
            mime[".png"] = "image/png";
            mime[".txt"] = "text/plain";
            mime[".mp3"] = "audio/mp3";
            mime["default"] = "text/html";
        }
        pthread_mutex_unlock(&lock);
    }
    if (mime.find(suffix) == mime.end())
        return mime["default"];
    else
        return mime[suffix];
}

std::priority_queue<std::shared_ptr<mytimer>, std::deque<std::shared_ptr<mytimer>>, timerCmp> mytimerQueue;

requestData::requestData():
    now_read_pos(0),
    state(STATE_PARSE_URI),
    h_state(h_start),
    keep_alive(false),
    againTimes(0)
{
    cout << "requestData()" << endl;
}

requestData::requestData(int _epollfd, int _fd, std::string _path):
        now_read_pos(0),
        state(STATE_PARSE_URI),
        h_state(h_start),
        keep_alive(false),
        againTimes(0),
        path(_path),
        fd(_fd),
        epollfd(_epollfd)
{
    cout << "requestData()" << endl;
}

requestData::~requestData() {
    cout << "~requestData()" << endl;
    close(fd);
}

void requestData::addTimer(shared_ptr<mytimer> mtimer)
{
    timer = mtimer;
}

int requestData::getFd()
{
    return fd;
}
void requestData::setFd(int _fd)
{
    fd = _fd;
}

void requestData::reset()
{
    againTimes = 0;
    content.clear();
    file_name.clear();
    path.clear();
    now_read_pos = 0;
    state = STATE_PARSE_URI;
    h_state = h_start;
    headers.clear();
    keep_alive = false;
    if (timer.lock())
    {
        shared_ptr<mytimer> my_timer(timer.lock());
        my_timer->clearReq();
        timer.reset();
    }
}

void requestData::seperateTimer()
{
    if (timer.lock())
    {
        shared_ptr<mytimer> my_timer(timer.lock());
        my_timer->clearReq();
        timer.reset();
    }
}

void requestData::handleRequest() {
    char buff[MAX_BUFF];
    bool isError = false;
    while(true){
        int read_num = readn(fd, buff, MAX_BUFF);
        if(read_num < 0){
            perror("1");
            isError = true;
            break;
        }
        else if(read_num == 0){
            perror("read_num == 0");
            if(errno == EAGAIN){
                if(againTimes > AGAIN_MAX_TIMES){
                    isError = true;
                }
                else ++againTimes;
            }
            else if(errno != 0)
                isError = true;
            break;
        }
        std::string now_read(buff, buff+read_num);
        content += now_read;

        if(state == STATE_PARSE_URI){
            int flag = this->parse_URI();
            if(flag == PARSE_URI_AGAIN){
                break;
            }
            else if(flag == PARSE_URI_ERROR){
                perror("2");
                isError = true;
                break;
            }
        }
        if(state == STATE_PARSE_HEADERS){
            int flag = this->parse_Headers();
            if(flag == PARSE_HEADER_AGAIN)
                break;
            else if(flag == PARSE_HEADER_ERROR){
                perror("3");
                isError = true;
                break;
            }
            if(method == METHOD_POST)
            {
                state = STATE_RECV_BODY;
            }
            else
            {
                state = STATE_ANALYSIS;
            }
        }

        if(state == STATE_RECV_BODY){
            int content_length = -1;
            if (headers.find("Content-length") != headers.end())
            {
                content_length = stoi(headers["Content-length"]);
            }
            else
            {
                isError = true;
                break;
            }
            if (content.size() < content_length)
                continue;
            state = STATE_ANALYSIS;
        }

        if(state == STATE_ANALYSIS){
            int flag = this->analysisRequest();
            if (flag < 0)
            {
                isError = true;
                break;
            }
            else if (flag == ANALYSIS_SUCCESS)
            {

                state = STATE_FINISH;
                break;
            }
            else
            {
                isError = true;
                break;
            }
        }
    }
    if(isError) return;

    if(state == STATE_FINISH){
        if(keep_alive)
            this->reset();
        else
            return;
    }

    std::shared_ptr<mytimer> mtimer(new mytimer(shared_from_this(), 500));
    this->addTimer(mtimer);
    {
        MutexLockGuard lock;
        myTimerQueue.push(mtimer);
    }

    __uint32_t  _epo_event = EPOLLIN | EPOLLONESHOT;
    int ret = Epoll::epoll_mod(fd, shared_from_this(), _epo_event);
    if(ret < 0)
        return;
}

int requestData::parse_Headers() {
    string &str = content;
    int key_start = -1, key_end = -1, value_start = -1, value_end = -1;
    int now_read_line_begin = 0;
    bool notFinish = true;
    for (int i = 0; i < str.size() && notFinish; ++i)
    {
        switch(h_state)
        {
            case h_start:
            {
                if (str[i] == '\n' || str[i] == '\r')
                    break;
                h_state = h_key;
                key_start = i;
                now_read_line_begin = i;
                break;
            }
            case h_key:
            {
                if (str[i] == ':')
                {
                    key_end = i;
                    if (key_end - key_start <= 0)
                        return PARSE_HEADER_ERROR;
                    h_state = h_colon;
                }
                else if (str[i] == '\n' || str[i] == '\r')
                    return PARSE_HEADER_ERROR;
                break;
            }
            case h_colon:
            {
                if (str[i] == ' ')
                {
                    h_state = h_spaces_after_colon;
                }
                else
                    return PARSE_HEADER_ERROR;
                break;
            }
            case h_spaces_after_colon:
            {
                h_state = h_value;
                value_start = i;
                break;
            }
            case h_value:
            {
                if (str[i] == '\r')
                {
                    h_state = h_CR;
                    value_end = i;
                    if (value_end - value_start <= 0)
                        return PARSE_HEADER_ERROR;
                }
                else if (i - value_start > 255)
                    return PARSE_HEADER_ERROR;
                break;
            }
            case h_CR:
            {
                if (str[i] == '\n')
                {
                    h_state = h_LF;
                    string key(str.begin() + key_start, str.begin() + key_end);
                    string value(str.begin() + value_start, str.begin() + value_end);
                    headers[key] = value;
                    now_read_line_begin = i;
                }
                else
                    return PARSE_HEADER_ERROR;
                break;
            }
            case h_LF:
            {
                if (str[i] == '\r')
                {
                    h_state = h_end_CR;
                }
                else
                {
                    key_start = i;
                    h_state = h_key;
                }
                break;
            }
            case h_end_CR:
            {
                if (str[i] == '\n')
                {
                    h_state = h_end_LF;
                }
                else
                    return PARSE_HEADER_ERROR;
                break;
            }
            case h_end_LF:
            {
                notFinish = false;
                key_start = i;
                now_read_line_begin = i;
                break;
            }
        }
    }
    if (h_state == h_end_LF)
    {
        str = str.substr(now_read_line_begin);
        return PARSE_HEADER_SUCCESS;
    }
    str = str.substr(now_read_line_begin);
}

int requestData::parse_URI() {
    std::string &str = content;
    int pos = str.find('\r', now_read_pos);
    if(pos < 0)
        return PARSE_URI_AGAIN;
    std::string request_line = str.substr(0, pos);
    if(str.size() > pos+1)
        str = str.substr(pos+1);
    else
        str.clear();
    pos = request_line.find("get");
    if (pos < 0)
    {
        pos = request_line.find("POST");
        if (pos < 0)
        {
            return PARSE_URI_ERROR;
        }
        else
        {
            method = METHOD_POST;
        }
    }
    else
    {
        method = METHOD_GET;
    }
    pos = request_line.find("/", pos);
    if(pos < 0){
        return PARSE_URI_ERROR;
    }
    else{
        int _pos = request_line.find(' ', pos);
        if(_pos < 0)
            return PARSE_URI_ERROR;
        else{
            if(_pos - pos > 1){
                file_name = request_line.substr(pos+1, _pos - pos - 1);
                int __pos = file_name.find('?');
                if(__pos >= 0)
                    file_name = file_name.substr(0, __pos);
            }
            else
                file_name = "index.html";
        }
        pos = _pos;
    }
    pos = request_line.find("/", pos);
    if(pos < 0)
        return PARSE_URI_ERROR;
    else{
        if(request_line.size() - pos <= 3)
            return PARSE_URI_ERROR;
        else{
            std::string ver = request_line.substr(pos+1, 3);
            if(ver == "1.0")
                HTTPversion = HTTP_10;
            else if(ver == "1.1")
                HTTPversion = HTTP_11;
            else
                return PARSE_URI_ERROR;
        }
    }
    state = STATE_PARSE_HEADERS;
    return PARSE_URI_SUCCESS;
}

void mytimer::update(int timeout)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    expired_time = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool mytimer::isvalid()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    size_t temp = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
    if (temp < expired_time)
    {
        return true;
    }
    else
    {
        this->setDeleted();
        return false;
    }
}

void mytimer::clearReq()
{
    request_data.reset();
    this->setDeleted();
}

void mytimer::setDeleted()
{
    deleted = true;
}

bool mytimer::isDeleted() const
{
    return deleted;
}

size_t mytimer::getExpTime() const
{
    return expired_time;
}

bool timerCmp::operator()(std::shared_ptr <mytimer> &a, std::shared_ptr <mytimer> &b) const {
    return a->getExpTime() > b->getExpTime();
}

MutexLockGuard::MutexLockGuard(){
    pthread_mutex_lock(&lock);
}

MutexLockGuard::~MutexLockGuard(){
    pthread_mutex_unlock(&lock);
}