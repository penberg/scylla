#!/bin/bash -e

source $(dirname $0)/util.sh

source /etc/os-release

SCYLLA_REPO_URL=$SCYLLA_REPO_URL_PREFIX/centos/scylladb-$SCYLLA_RELEASE.repo

echo "Installing Scylla $SCYLLA_VERSION on $PRETTY_NAME from $SCYLLA_REPO_URL..."

rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
yum install -y -q deltarpm epel-release
curl -s -o /etc/yum.repos.d/scylla.repo -L $SCYLLA_REPO_URL
yum install -y -q scylla-$SCYLLA_VERSION
