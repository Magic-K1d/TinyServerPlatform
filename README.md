TinyServerPlatform
=========
个人小型服务端框架，学习用，参考各种开源框架（TinyHttpd，TinyWebServer，Zeus，Sinetlib等）。

### 目前已实现
+ Server:监听服务器端口，创建新连接
+ Event：统一事件源（目前实现读写事件）
+ Epoller：利用Event对Epoll进行封装
+ Threadpool：使用优先队列实现带优先级的线程池

+ Client：使用Epoll监听输入fd，向指定服务器发送消息

### TODO
+ Connection：对连接进行抽象，存储连接信息，实现读写等接口
+ Http：状态机实现http解析，cgi服务等
