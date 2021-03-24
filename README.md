TinyServerPlatform
=========
个人小型服务端框架，学习用，参考各种开源框架（TinyHttpd，TinyWebServer，Zeus，Sinetlib等）。
正在逐步实现中，提交代码均为测试通过代码

### 目前已实现
+ Server:监听服务器端口，创建新连接
+ Event：统一事件源（目前实现读写事件）
+ Epoller：利用Event对Epoll进行封装
+ Threadpool：使用优先队列实现带优先级的线程池
+ Connection：对连接进行抽象，存储连接信息，实现读接口

+ // Client：使用Epoll监听输入fd，向指定服务器发送消息

### TODO
+ Server：注册
+ Event：多事件支持，活动事件优化
+ Connection：写接口,中断回调等
+ IOBuffer
+ Logger
+ HttpServer
