# Preface

这*暂时*是一个专门配合课表使用的小东西，作用是生成一个通用的日历文件，使之能在几乎**全平台**的**系统日历**中，**原生地**显示课表。

我自己是有这样需求，把课表导入到系统日历中，这样的话：

- 多设备同步。不少厂商都有不错的云服务，可以在电脑平板手机之间共享日历

- 更好的提示。操作系统总是对系统日历更加友好，配合小组件，系统日历总是比一张PDF更易用

(如果有) 后续更新🔗[期望](#epilogue)

废话太多，直接看🔗[方法](#usage)！

## 一些废话 (不用看，点前面链接跳转) 

### 关于原理

我以前真是不懂，从没思考过 `.c` 文件是一种什么文件，经常听人“装B”说：“我写代码都用记事本写”，却没考虑过这背后是啥意思。或者说，我从未考虑过“文件类型”究竟代表了什么。

后来在 CSAPP 第一章里看到了这么一句话：

> Files such as `hello.c` that consist exclusively of ASCII characters are known as *text ﬁles*. All other ﬁles are known as *binary ﬁles*.

(记得之前玩文件的读写的时候把 `txt` 改成了 `c`，程序运行的同样很好。这么明显了我都没意识到…) 

所以后来发现很多日历软件都能到导出一种叫 `ics` 的文件，结果用记事本尝试打开了一下，BOOM! 是个文本文件

那么只要搞清楚它内部是怎么编排的，生成所谓的日历文件，其实跟任何语言都会讲的读写 `txt` 没有任何区别

### 关于对这个东西本身

这样看来，其实清楚的知道，这个东西*到现在为止*，技术含量其实不高，用什么语言都能实现

那为什么这里是 C++ 呢？因为其实正好在学它，由于 icsProducer 原理也简单，所以正好可以把它当作我学习过程中的一个“大作业”

那这样又会注意到，作为“大作业”它显得完成度不高：
- 行数不够
- 并没有用到什么 C++ 的特性

因为原理简单，功能单一，行数自然不多；C++ Primer 其实我也只读了 1/3，尚未接触太多语言特性 (很多还停留在 C 的程度)

确实，本来想要读完 C++ Primer 再来做这个东西，但貌似这个想法掉入“从明天开始”的陷阱了

另外，我必须在大二上结束之前尽快做出雏形，因为我想在大二下新的课表来的时候，亲手用用

另另外，github 毕竟也叫 git，这也是一个绝佳的机会去学习感受什么是 push，什么是 commit

另另另外，我想这也是一种敏捷软件开发 (Agile Software Development) ~~我的天呐，别给自己脸上贴金了~~

另另另另外，C++ 是面向对象的，日后修改源码的时候，我想能够有机会体会什么叫所谓的 
> a class may totally change how it stores its data, but as long as it continues to use the same methods to manipulate the data, no other object will know or care.

# Usage

只需准备两个 `.csv` 文件，分别存放

- 学校上下课的时间
- 课表的信息

不知道 `.csv` 也没事，直接用 Excel 做也可以，只要最后保存的时候选择 `csv`

<img src="pictures/wins.png" width="30%"> <img src="pictures/mac.png" width="30%">

## 学校上下课时间

仓库中提供的 `Timetable.csv` 是我记录的我们学校的时间表供参考。文件格式需求如下

| 课节     | 上课时间 | 下课时间 |
| -------- | -------- | -------- |
| 1        | 0800     | 0845     |
| 2        | 0850     | 0935     |
| ...      | ...      | ...      |
| 12       | 1940     | 2025     |
| 20220822 |          |          |

- 第一列的数字代表第几节课，比如 `1` 代表 `第一节` 
- 第二列的四位数字是上课时间，前两位代表“`时`”，后两位代表“`分`”
- 第三列就是下课时间
- 除此之外，在最后一行的第一个位置，需要写上第一周星期一的日期，比如 `20220822` 代表 `2022年8月22日`

然后另存为，选择 `CSV UTF-8`

## 课表的信息

仓库中提供的 `Schedule.csv` 是举例的课表文件供参考。文件格式需求如下

| 课程名   | 星期几 | 第几节到第几节 | 提前多久提醒 | 地点        | 第几周到第几周 | 每几周一次 | 备注信息     |
| -------- | ------ | -------------- | ------------ | ----------- | -------------- | ---------- | ------------ |
| Java     | 1      | 1 2            | 15           | 综合楼B 108 | 3 18           | 1          | 腾讯会议 xxx |
| Java     | 3      | 8 9            | 15           | 综合楼B 108 | 3 18           | 1          | 腾讯会议 xxx |
| 离散数学 | 4      | 3 5            |              | 一教 200    | 3 18           |            |              |
| Lorem    | 1      | 1 2            | `None`       | `None`      | 1 21           | 1          | `None`       |

- `第几节到第几节` 和 `第几周到第几周` 里两个数字中间用*空格*分开
- 对于一周上两次课的，比如例中一周上两次 Java，就单独为每次新建日程
- 所有这些都是选填的，而对于每一个未填空，默认生成的内容如最后一行显示。(None 代表啥也没有)

然后另存为，选择 `CSV UTF-8`

---


文件名建议使用英文和数字，文件所在路径不要出现中文 (中文 win 下运行不出，找不出臭虫) 

然后就可以打开程序，按照提示，先拖进去“校历”文件，也就是学校的上下课时间，回车，再拖进去“课表”文件，回车。`ics` 文件就出来啦！

## 导入系统目录

除 iOS 之外的任何设备，都可以直接打开 `ics` 文件 (比如 Windows MacOS Android)。比如安卓手机或者鸿蒙，可以直接文件传输助手把这个文件发过去，直接手机打开结束

但是苹果手机或者平板，就需要以下两种方法其一：

### 通过 iCloud

如果你有 Mac，因为 Mac 可以直接打开 `ics`，所以可以用电脑打开，利用同步到手机上

### 通过邮件

在手机上原生的邮箱应用里登录一个邮箱 (如果之前没登过的话建议直接创一个 iCloud 邮箱，在那里登 QQ 邮箱不是帐号密码这么简单) 

把 `ics` 发到这个邮箱上，然后手机通过邮箱打开这个文件，就可以导入日历了

或者文件传输先到手机上，然后用系统邮箱把这个 `ics` 发出去

**关键**就是通过*系统自带的邮件 app*，打开这个 `ics` 文件即可

---

如果你需要亲手编译一下，我对 shell 还不是特别熟悉，不过我能提供

```shell
# Windows
g++ -std=gnu++17 -o icsProducer.exe main.cpp Csv.cpp SchoolSchedules.cpp SchoolTimetable.cpp Date.cpp PixelFont.cpp -static
# Unix
g++ -std=gnu++17 -o icsProducer main.cpp Csv.cpp SchoolSchedules.cpp SchoolTimetable.cpp Date.cpp PixelFont.cpp
```

这样是能够正确的编译的 (记得先 `cd` 进源码文件夹) 

# Epilogue

还有很多基本的异常处理没去做，等我学了 C++ 异常处理

希望能把这个课表相关的 icsProducer 变为一个“插件”，属于一个新主体“CalendarToolbox”，能够处理更加通用的日程

希望能做成一个 web 应用，并且 `ics` 可以用订阅的方式导入，不过具体怎么实施我还不晓得

希望能有更好的导入课表的方式，比如爬爬教务处课表网页？



