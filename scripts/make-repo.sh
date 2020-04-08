#!/bin/bash -e

REPO_ROOT=$(pwd)/repo

SCYLLA_REPOFILE=$REPO_ROOT/scylla.repo

SCYLLA_REPO=$REPO_ROOT/scylla

SCYLLA_REPO_URL_PREFIX=<insert prefix here>

SCYLLA_S3_PATH=<insert S3 path here>

DBUILD_PATH=$(pwd)/tools/toolchain/dbuild

SERVER_GIT_PATH=$(pwd)

TOOLS_GIT_PATH=$(pwd)/../scylla-enterprise-tools-java

JMX_GIT_PATH=$(pwd)/../scylla-enterprise-jmx

AMI_GIT_PATH=$(pwd)/../scylla-enterprise-ami

function build_reloc () {
  GIT_PATH=$1
  cd $GIT_PATH
  $DBUILD_PATH ./reloc/build_reloc.sh
  $DBUILD_PATH ./reloc/build_rpm.sh
}

function build_python () {
  GIT_PATH=$1
  cd $GIT_PATH
  $DBUILD_PATH ./reloc/python3/build_reloc.sh
  $DBUILD_PATH ./reloc/python3/build_rpm.sh
}

function build_ami () {
  GIT_PATH=$1
  cd $GIT_PATH
  ./dist/redhat/build_rpm.sh --target centos7
}

mkdir -p $SCYLLA_REPO

#build_reloc $JMX_GIT_PATH
#build_reloc $TOOLS_GIT_PATH
#build_reloc $SERVER_GIT_PATH
#build_python $SERVER_GIT_PATH
#build_ami $AMI_GIT_PATH

#cp -R $SERVER_GIT_PATH/build/redhat/RPMS/x86_64 $SCYLLA_REPO/
#cp -R $JMX_GIT_PATH/build/redhat/RPMS/noarch $SCYLLA_REPO/
#cp -R $TOOLS_GIT_PATH/build/redhat/RPMS/noarch $SCYLLA_REPO/
#cp -R $AMI_GIT_PATH/build/RPMS/noarch $SCYLLA_REPO/

createrepo_c --quiet $SCYLLA_REPO/x86_64
createrepo_c --quiet $SCYLLA_REPO/noarch

cat <<EOT > $SCYLLA_REPOFILE 
[scylla]
name=Scylla for CentOS \$releasever - \$basearch
baseurl=$SCYLLA_REPO_URL_PREFIX/scylla/\$basearch/
enabled=1
gpgcheck=0

[scylla-generic]
name=Scylla for CentOS \$releasever
baseurl=$SCYLLA_REPO_URL_PREFIX/scylla/noarch/
enabled=1
gpgcheck=0
EOT

echo "Repository in $REPO_ROOT is ready to be uploaded!"
