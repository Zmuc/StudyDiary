#!/bin/bash

# 定义唯一时间戳
TIMESTAMP=$(date "+%Y%m%d%H%M%S")

# 打deb包
function pack_deb {
	if [ ! -f $1/DEBIAN/control ]; then
		echo "打包目标无deb control，退出..."
		return
	fi

	mkdir deb_build_$TIMESTAMP
	dpkg-deb -b $1 deb_build_$TIMESTAMP/

	echo "打包于 $PWD/deb_build_$TIMESTAMP"
}

# 解deb包
function untie_deb {
	file $1 | grep 'Debian binary package'
	if [ $? -ne 0 ]; then
		echo "解包目标非deb安装包，退出..."
		return
	fi

	mkdir -p deb_source_$TIMESTAMP/DEBIAN
	dpkg -X $1 deb_source_$TIMESTAMP
	dpkg -e $1 deb_source_$TIMESTAMP/DEBIAN

	echo "解包于 $PWD/deb_source_$TIMESTAMP"
}

# 帮助
function show_help {
	echo -e "[HELP] 用法：deb-compress-tool.sh [选项] | [文件]\n"
	echo "   -c    归档deb安装包"
	echo "   -x    解开deb安装包"
	echo "   -h    帮助信息"
	echo "   -v    版本信息"
}

# 版本信息
function show_info {
	echo -e "deb-compress-tool v1.0\n"
	echo "适用于debian deb包快速压缩解压"
}

# 参数/选项，$OPT为选项，$OPTARG为选项参数
# x:带参，x不带参
while getopts "x:c:hv" OPT;
do
	case $OPT in
		x)
			untie_deb $OPTARG
			break
			;;
		c)
			pack_deb $OPTARG
			break
			;;
		h)
			show_help
			break
			;;
		v)
			show_info
			break
			;;
		*)
			show_help
			break
			;;
	esac
done
