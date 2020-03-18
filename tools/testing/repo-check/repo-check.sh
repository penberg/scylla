#!/bin/bash -e

PROGRAM=$(basename $0)

print_usage() {
    echo "Usage: $PROGRAM [OPTION]..."
    echo ""
    echo "  --version VERSION      The Scylla version to check (for example, 3.2.3)."
    echo "  --repo-url-prefix URL  The Scylla repository URL prefix to check."
    echo "  --gpg-key KEY          The public GPG key to verify signed packages."
    exit 1
}

while [ $# -gt 0 ]; do
    case "$1" in
        "--version")
            VERSION=$2
            shift 2
            ;;
        "--repo-url-prefix")
            REPO_URL_PREFIX=$2
            shift 2
            ;;
        "--gpg-key")
            GPG_KEY=$2
            shift 2
            ;;
        "--help")
            print_usage
            ;;
        *)
            print_usage
            ;;
    esac
done

if [ -z "$VERSION" ] || [ -z "$REPO_URL_PREFIX" ] || [ -z "$GPG_KEY" ]; then
    print_usage
fi

WORKDIR="/testing"

# Install Scylla.
#
# Parameters:
#  docker_image  The Docker image to test Scylla in.
#
install () {
  docker_image=$1
  docker run -it --rm -v $(pwd):$WORKDIR $docker_image /bin/bash -c "cd $WORKDIR && ./tools/testing/repo-check/install-$docker_image.sh --version $VERSION --repo-url-prefix $REPO_URL_PREFIX --gpg-key $GPG_KEY"
}

install centos:7
