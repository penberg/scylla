#!/bin/bash

source $(dirname $0)/util.sh

echo "Installing Scylla ($MODE) packages on $PRETTY_NAME..."

rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
yum install -y -q deltarpm
yum update -y -q
yum install -y $SCYLLA_RPMS
