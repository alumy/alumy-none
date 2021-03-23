#!/bin/bash

YUM=$(which yum 2>/dev/null)
APT=$(which apt 2>/dev/null)

source /etc/os-release

echo "$NAME $VERSION"

if [ -x "$YUM" ]; then
	rpm -Uvh https://packages.microsoft.com/config/rhel/7/packages-microsoft-prod.rpm
	yum makecache
	yum install -y cmake3 ccache dotnet-runtime-3.1
fi

if [ -x "$APT" ]; then
	wget https://packages.microsoft.com/config/ubuntu/$VERSION_ID/packages-microsoft-prod.deb -O /tmp/packages-microsoft-prod.deb
	dpkg -i /tmp/packages-microsoft-prod.deb
	rm /tmp/packages-microsoft-prod.deb

	apt update -y
	apt install -y apt-transport-https
	apt install -y dotnet-runtime-3.1
	
	apt install -y cmake ccache
fi

echo -e 'export PATH=$PATH:/opt/gcc-arm-none-eabi-10-2020-q4-major/bin' > /etc/profile.d/gcc-arm-none-eabi.sh

exit 0

