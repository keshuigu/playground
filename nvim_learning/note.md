# Nvim

## 1

1. 退出vim: `:quit`, `:q`, `:qa`
2. 帮助手册: `:help`, `:h`, 例如: `:help :qa`
3. `:q` 和`:qa` 的区别: `:q`退出当前窗口, `:qa`退出全部窗口
4. 模式: `Normal mode`, `Insert mode`, `Visual mode`, `Select mode`, `Command-Line mode`, `Ex mode`
5. 打开文件: `nvim oeasy.txt`
6. 查看文件信息: `:f`, `Ctrl + G`
7. 基础光标移动: `h`左移,`j`下移, `k`上移, `l`右移
8. vim键盘图: 

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404171238889.gif)

9. 跳入链接: `Ctrl + ]`; 跳出链接: `Ctrl + o`
10. 退回到命令模式: `Ctrl + c` 或者 `esc`
11. `:q!` 强制退出, 不保存
12. `:saveas file.txt`: 另存为file.txt
13. `:w` 保存修改, 文件名后有`[+]`表示有修改
14. `.` 重复刚才的操作; `u` 撤销上一步操作; `Ctrl + r` 重做上一次操作

## 2

1. 插入:

	- `i` 在光标前插入
	- `I` 在光标所在行所有文本的最前面插入
	- `gI` 在光标所在行最前面插入

2. 追加:
	
	- `a` 在光标后插入
	- `A` 在光标所在行所有文本的最后面插入

3. `:w file.txt` 覆盖写入file.txt
4. `:w >> file.txt` 追加写入file.txt
5. 下方插入:

	- `o` 光标所在行下面插入一个空行
	- `O` 光标所在行上面插入一个空行

6. 显示行号: `:set nu`

## 3

1. 插入-普通模式: 执行一次`普通模式`的操作 `Ctrl + o`, 举例而言，如果在编辑时想要保存文件，可以:
	
	- `ctrl + o`
	- `:w`
	- 执行完毕后仍然处于插入模式

2. 按`word`进行移动: 

	- `w` 移动到下一个单词的开头 
	- `b` 移动到当前单词的开头, 如果已经在开头了, 那么会移动到上一个单词的开头
	- `e` 移动到当前单词的结尾, 如果已经在结尾了, 那么会移动到下一个单词的结尾
	- `ge` 向前移动到上个单词的词尾
	- 在字母前加数字代表重复操作, 如`2w` 就是`w`两次, 不止局限于移动操作

3. `word`与`WORD`区别: `word` 认为 `=`, `"` 之类的符号都是分割符; `WORD` 认为只有`空格`, `tab`, `换行` 是分割符
4. 按`WORD`进行移动: `W`, `B`, `E`, `gE` 用法与小写字母相同, 仅是识别的分割符不同
5. `^`: 移动到行首, 本行第一个非空字符
6. `0`: 移动到行首，本行第一个字符
7. `g_`: 移动到行尾, 本行最后一个非空字符
6. `$`: 移动到行尾, 本行最后一个字符


## 4

1. 行内向后查找字符c: `fc`, 此处c为需要查找的字符
2. `;` 继续同方向查找， `,` 反向查找
3. `F`: `f`的反向操作
4. `t`: 贴靠字符，跳到查找字符的前一个字符上，贴靠着查找字符
5. `T`: `t`的反向操作
6. 总结: 小写相关是向前，大写相关是向后，`;`维持原方向，`,`反方向
7. `-`跳至上一行行首非空字符，`+`跳至下一行行首非空字符
8. `+`相当于`j ^`，`-`相当于`k ^`
9. `gg` 跳至首行，`G`跳至尾行
10. `[count] G`,跳转至[count]行
11. `[count] |`,跳转至[count]列
12. `[count] %`,跳转至整个文件的[count]%

## 5

1. `:se[t] nu[mber]` 显示行号
2. `:se[t] nonu[mber]` 关闭显示行号
3. `:se[t] relativenumber` 显示相对于光标的行号，简写为`:set rnu`
4. `:se[t] norelativenumber` 关闭显示相对行好，简写为`:set nornu`
5. `:[count]` 跳转到count行,绝对行号
6. ``` `` ```:返回跳转前的位置
7. 跳转列表: 保存所有的跳转记录
8. `ctrl-o`:向旧的位置/上一次的位置跳转
9. `ctrl-i`:向新的位置/下一次的位置跳转

## 6

1. `:marks`查看所有标记
2. `ma`定义标记为`a`的跳转位置
3. `:delm a`删除标记a
4. `''`上次跳转操作光标位置
5. `'"`上次退出文件位置
6. `'[`上次编辑的开始位置
7. `']`上次编辑的结束位置
8. `'.`上次编辑的最后操作位置
