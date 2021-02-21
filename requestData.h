//
// Created by wx on 2/21/21.
//

#ifndef MYHTTPSERVER_REQUESTDATA_H
#define MYHTTPSERVER_REQUESTDATA_H

#include <pthread.h>
#include <string>
#include <unordered_map>
#include <memory>


class MimeType{
private:
    static pthread_mutex_t lock;
    static std::unordered_map<std::string, std::string> mime;
    MimeType();
    MimeType(const MimeType &m);
public:
    static std::string getMime(const std::string &suffix);
};

enum HeadersState{
    h_start = 0,
    h_key,
    h_colon,
    h_spaces_after_colon,
    h_value,
    h_CR,
    h_LF,
    h_end_CR,
    h_end_LF
};

struct mytimer;
class requestData{
private:
    int againTimes;
    std::string path;
    int fd;
    int epollfd;
    // content的内容用完就清
    std::string content;
    int method;
    int HTTPversion;
    std::string file_name;
    int now_read_pos;
    int state;
    int h_state;
    bool isfinish;
    bool keep_alive;
    std::unordered_map<std::string, std::string> headers;
    std::weak_ptr<mytimer> timer;


private:
    int parse_URI();
    int parse_Headers();
    int analysisRequest();

public:

    requestData();
    requestData(int _epollfd, int _fd, std::string _path);
    ~requestData();
    void addTimer(std::shared_ptr<mytimer> mtimer);
    void reset();
    void seperateTimer();
    int getFd();
    void setFd(int _fd);
    void handleRequest();
    void handleError(int fd, int err_num, std::string short_msg);
};

struct mytimer{
    bool deleted;
    size_t expired_time;
    std::shared_ptr<requestData> request_data;

    mytimer(std::shared_ptr<requestData> _request_data, int timeout);
    ~mytimer();
    void update(int timeout);
    bool isvalid();
    void clearReq();
    void setDeleted();
    bool isDeleted() const;
    size_t getExpTime() const;
};

struct timerCmp
{
    bool operator()(std::shared_ptr<mytimer> &a, std::shared_ptr<mytimer> &b) const;
};

class MutexLockGuard{
public:
    explicit  MutexLockGuard();
    MutexLockGuard(const MutexLockGuard&) = delete;
    MutexLockGuard& operator=(const MutexLockGuard&) = delete;
    ~MutexLockGuard();

private:
    static pthread_mutex_t lock;
};

#endif //MYHTTPSERVER_REQUESTDATA_H
