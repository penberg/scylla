# Backport queue

Bug fixes in Scylla are always merged to the master branch. However, in many
cases, the fix needs to be backported to release branches. The backport queue
is a list of issues that are with the `Backport candidate` label on
Github issues. When a commit is promoted to the master branch, a backlog
queue bot is triggered, which parses git commit messages and labels
issues automatically as per the following rules:

- If a commit message contains the `Fixes: #1234` tag, the issue is
  tagged with the `Backport candidate` label. Patch submitters may amend
  the commit message with additional `Branches: 3.0, 2.3` attribute to
  specify which branches need a backport.

- For issues that don't need to be backported, patch submitted *must*
  use the `Branches: master` attribute in the commit message to avoid
  backlog queue bot from labeling the issue.
