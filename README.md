# 7天一个QQ
<p>    首先，介绍一下我的这个QQ~~它是用ADO数据库、WinSocket网络通信、多线程等，写成的~~</p>

<p>    其实原来是准备是用p2p让两个客户端直接通信的~~但后来总是不成功，从网上下了别人编好的p2p打洞的例子exe，找了服务器和
另一个局域网的电脑来测试，结果人家的示例也不成功~~怀疑是我的小米路由器禁止了这种打洞行为~~</p>
    
<p>    所以无奈，只好用服务器转发的方式完成了两客户端通信~~虽然没技术含量，不过用户体验貌似不错~~</p>

---------------------------------------------------------------------------------------------------------------------------------

<p>    对了，再罗嗦一句：我的服务器绑定的端口是5088~~而客户端连接的是 zhangsheng377.wicp.net:32137 ~~
这是因为我在我的电脑上是用花生壳穿透内网来充当服务器的~~</p>

<p>    至于真正的服务器，也在上面测试过，完全成功~~当时在阿里云上买了一个按时付费的云服务器，把服务器端放在上面，
找了不同地方的同学，可以完美通信~~并且比我的电脑当服务器稳定多了~~只可惜云服务器太贵，所以只开了一个晚上就把它释放掉了~~</p>

---------------------------------------------------------------------------------------------------------------------------------

<p>    再说一下现在还没完成的部分:</p>
            1.删除好友
            2.同一个号重复登陆
            3.一台电脑上的所有客户端都是用同一个数据库~~所以其实他们的好友表都是一样的~你之所以看着不一样,
                那仅仅是还没刷新~~~呃,你问刷新按钮在哪?~~~呃,我还没编呢~不过当你添加好友或是重新登录时,
                它都会自动刷新~~
            4.如果聊天的时候,自己不是对方的好友,则对方不会收到信息~而且自己这边也没任何提示~~~~
                我承认这是一个重大bug,但其实主要是我懒得做了~~

---------------------------------------------------------------------------------------------------------------------------------

<p>    这个项目的由来其实是我这个月开始学mfc嘛~~正好书的最后一章就是socket，还留了一个思考题：让我们编一个网络聊天室~~
没有代码~~~~然后嘛，编着编着我就想，既然我都编一个聊天室了，那为什么不进一步，编一个QQ呢？~~</p>

---------------------------------------------------------------------------------------------------------------------------------

<p>    接下来就是，我准备有时间再开一个项目，实验UDP的p2p打洞~~成功后再试验TCP的打洞~~~~等都弄好后，
我准备再回来把这个项目的代码重构一下·~因为我觉得里面的逻辑有点混乱~代码有些地方也没复用~~总之就是看得不清晰~~</p>
    
<p>    当然啦~明天就要去学车了~一周后科目二考试~~难得的清闲时光已经没有了~~我还要去学stm32~网课已经开始了~~
还有就是网络技术的书，要尽快看完~~~~~</p>
    
<p>    嗯~~未来就是这样~~~~~</p>
