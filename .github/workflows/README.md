# GitHub Actions

## Release Asset
- Watch this YouTube video [Creating a GitHub release in a GitHub Actions workflow](https://www.youtube.com/watch?v=_ueJ3LrRqPU&t=40s&ab_channel=MicrosoftDevRadio)

## GITHUB_TOKEN
- Getting this error from a GitHub Action step?
```
Error: Resource not accessible by integration
```
- The GITHUB_TOKEN needs to have read and write enabled
  - Repo > Settings > Actions > General

![Screenshot of Workflow permissions selecting Read and write permissions](../assets/workflow_permissions.png)
