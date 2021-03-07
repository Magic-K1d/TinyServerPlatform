# TinyServerPlatform
个人小型服务端框架，参考开源服务端框架（例如TinyHttpd等）。

### 目前已实现
+Threadpool：使用优先队列实现带优先级的线程池
+Event：统一事件源（目前实现读写事件）
+Epoller：利用Event对Epoll进行封装

### TODO
+Connection：对连接进行抽象，存储连接信息，实现读写等接口
+Http：状态机实现http解析，cgi服务等
