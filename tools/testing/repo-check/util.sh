PROGRAM=$(basename $0)

print_usage() {
    echo "Usage: $PROGRAM [OPTION]..."
    echo ""
    echo "  --version VERSION      The Scylla version to check (for example, 3.2.1)."
    echo "  --repo-url-prefix URL  The Scylla repository URL prefix to check."
    echo "  --gpg-key KEY          The public GPG key to verify signed packages."
    exit 1
}

while [ $# -gt 0 ]; do
    case "$1" in
        "--version")
            SCYLLA_VERSION=$2
            shift 2
            ;;
        "--repo-url-prefix")
            SCYLLA_REPO_URL_PREFIX=$2
            shift 2
            ;;
        "--gpg-key")
            SCYLLA_GPG_KEY=$2
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

if [ -z "$SCYLLA_VERSION" ] || [ -z "$SCYLLA_REPO_URL_PREFIX" ] || [ -z "$SCYLLA_GPG_KEY" ]; then
    print_usage
fi

SCYLLA_MAJOR=$(echo $SCYLLA_VERSION | cut -d. -f1)
SCYLLA_MINOR=$(echo $SCYLLA_VERSION | cut -d. -f2)
SCYLLA_RELEASE="$SCYLLA_MAJOR.$SCYLLA_MINOR"
