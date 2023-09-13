#pragma once
#include <string>
#include "TcpServer.hpp"
#include <memory>
#include "split.hpp"
#include <string.h>
#include <string>
#include "util.hpp"

#define SEP 'X'
#define SEP_LEN sizeof(SEP)
#define SPACE " "
#define SPACE_LEN strlen(SPACE)
#define LINE "\r\n"

extern Response GET(const Request &req);
extern Response POST(const Request &req);
extern Response DELETE(const Request &req);
extern Response PUT(const Request &req);
extern int BeginHandler(Connection *conn, std::string &str);
int HandlerRequest(Connection *conn, std::string &str)
{
  return BeginHandler(conn, str);
}

class Server
{
public:
  Server(int port) : _port(port)
  {
    // std::cout << "核力量" << std::endl;
  }
  ~Server()
  {
  }

  void SetMountPoint(std::string str)
  {
    _root += str; // 设置静态根目录
    std::cout << _root << std::endl;
  }
  void Listen()
  {
    std::unique_ptr<TcpServer> reactor(new TcpServer(_port, splitPagce, HandlerRequest));
    reactor->Run();
  }

public:
  static std::string GetRoot()
  {
    return _root;
  }

private:
  uint16_t _port;
  static std::string _root;
};
std::string Server::_root;

void parse_uri(char *uri, char *filename)
{

  std::string root = Server::GetRoot();
  sprintf(filename, "%s", root.c_str());
  if (*uri == '/' && strlen(uri) == 1)
    sprintf(filename, "%s/index.html", filename);
  else
    sprintf(filename, "%s%s", filename, uri);
}
// 解码
bool Parser(std::string &str, struct Request *req)
{

  char m_u_v[100] = {0};
  char *pch = strstr((char *)str.c_str(), LINE);  // 寻找第一行
  strncpy(m_u_v, str.c_str(), pch - str.c_str()); // 拷贝
  req->method = strtok(m_u_v, SPACE);
  req->uri = strtok(NULL, SPACE);
  req->version = strtok(NULL, SPACE);
  // 这里应该找到主体,先不看
  return true;
}
// 序列化
void Serialize(std::string *out, struct Response *resp)
{
  *out += resp->version + SPACE + resp->status + SPACE + resp->explain + LINE;
  // *out += "Content-length: " + std::to_string(resp->length) + LINE;
  // *out += "Content-type: " + resp->type + LINE;
  *out += "Connection: Keep-Alive";
  *out += LINE;
  *out += LINE;
  *out += resp->body;
}

// 这个就是我们业务就可以了
int BeginHandler(Connection *conn, std::string &str)
{
  // 读取到了报文,进行反序列化
  struct Request req;

  if (!Parser(str, &req))
  {
    return -1;
  }
  const char *method = req.method.c_str();
  // 把请求给分割了
  struct Response resp;
  // 进行请求的读取
  if (strcmp("GET", method) == 0)
  {
    resp = GET(req);
  }
  else if (strcmp("PUT", method) == 0)
  {
    resp = PUT(req);
  }
  else if (strcmp("Post", method) == 0)
  {
    resp = POST(req);
  }
  else if (strcmp("Delete", method) == 0)
  {
    resp = DELETE(req);
  }
  else
  {
  }

  std::string outbuffer;
  Serialize(&outbuffer, &resp);
  conn->outbuffer += outbuffer;
  conn->sender_(conn);
  if (conn->outbuffer.empty())
    conn->R->EnableReadWrite(conn->sock_, true, false);
  else
    conn->R->EnableReadWrite(conn->sock_, true, true);
  return 1;
}

Response GET(const Request &req)
{

  char filename[1024];
  parse_uri((char *)req.uri.c_str(), filename);
  struct Response resp;
  resp.version = "HTTP/1.0";
  resp.status = "200";
  resp.explain = "OK";
  // umask(0);
  int read_fd = open(filename, O_RDWR, 0666);
  char buffer[100000] = {0};
  ssize_t s = read(read_fd, buffer, sizeof(buffer) - 1);
  buffer[s] = 0;
  resp.body += buffer;
  std::cout << "--------------------------" << std::endl;
  std::cout << resp.body << std::endl;
  std::cout << "--------------------------" << std::endl;
  // resp.type = "HTML";
  resp.length = s;
  return resp;
}

Response POST(const Request &req) {}
// Response GET(const Request &req) {}
Response DELETE(const Request &req) {}
Response PUT(const Request &req) {}
