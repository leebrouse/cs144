## NOTE:
### If you see this waring during you configue the lab experience:
`````
root@LAPTOP-LDK0D967:~/cs144/minnow# ./scripts/make-parallel.sh 
bash: ./scripts/make-parallel.sh: /bin/sh^M: bad interpreter: No such file or directory
`````

### Solution:
使用 dos2unix 工具将文件转换为 Unix 风格换行符：

bash
`````
sudo apt-get install dos2unix  # 如果未安装 dos2unix
dos2unix ./scripts/make-parallel.sh
`````