# HW0 - Intro. to Compiler Design

## 4 tasks

1. Ensure the environment is correct for further homeworks

2. Using "Docker"

3. Using "GNU Make"

4. Using "Git" to manage project and hand in the homework

## For Windows User

If you are using Windows, please use Virtual Machine to run an Ubuntu system.

### Virtual Machine
- [VMware Workstation Player](https://www.vmware.com/products/workstation-player/workstation-player-evaluation.html)
- [Oracle VM VirtualBox](https://www.virtualbox.org/)

### ISO image
- [Ubuntu 18.04](https://ubuntu.com/download/server/thank-you?country=TW&version=18.04.4)

## Step0. Install Docker

Install Docker：

```sh
$ sudo apt-get update
$ sudo apt-get remove docker docker-engine docker.io
$ sudo apt-get install docker.io
```
Check Docker status：

```sh
$ docker --version
$ sudo service docker start
$ sudo service docker enable # active docker service at sys boot
$ service docker status
```

To make your Docker `sudo` free, use following command：

```sh
$ sudo groupadd docker
$ sudo gpasswd -a $USER docker
$ sudo service docker restart
```

## Step1. Install Git

```sh
$ sudo apt-get install git
$ git --version
```

### Setting git configuration

```sh
$ git config --global user.name your_github_id
$ git config --global user.email "email@example.com"
$ cat ~/.gitconfig # check the configuration
```

## Step2. Install Make

```sh
$ sudo apt-get install make
```

## Step3. git clone HW0 Repository
Get repo URL of HW0:
![](https://i.imgur.com/3VpC0cK.png)

Use the following command:
```sh
$ git clone <repo URL>
$ cd <repo NAME>/
```

## Step4. Fetch hw0 Docker image

```shell
$ make docker-pull # Get docker image of hw0

docker pull ianre657/compiler-s20-hw0:latest
latest: Pulling from ianre657/compiler-s20-hw0
Digest: sha256:f9fe0fdb4d1d048414b3e40f11097b0548fc6be4e06fc4f5a1c1319557c29dd0
Status: Image is up to date for ianre657/compiler-s20-hw0:latest
docker.io/ianre657/compiler-s20-hw0:latest
```

Check the installation:
```sh
$ docker image ls | grep hw0

ianre657/compiler-s20-hw0      latest              d1457c631c72        8 days ago          220MB
```

Enter Docker:
```sh
$ sudo ./activate_docker.sh
```

## Step5. Update `student_info.ini` and `README.md` 

Updating `student_info.ini` to your personal info, you can do this in original OS.

Updating `README.md`: This process SHOULD be done in Docker
```sh
$ make
$ cat README.md
```

The content should like this:
```
#HW0 環境熟悉

|||
|:-:|:-:|
|Name|<Name>|
|ID|<ID>|
|GitHub|<Github ID>|
|Email|<email@example.com>|
> **請修改 `student_info.ini` 並執行程式更新資訊**

+ Last Make: `2020-09-16 02:45:37 PM`

+ Docker ENV FLAG: `DOCKER_ACTIVATED`
...
```

## Step6. Update Repository in Github

Check git status:
```sh
$ git status
On branch master
Your branch is up to date with 'origin/master'.

Changes not staged for commit:
    (use "git add <file>..." to update what will be committed)
    (use "git checkout -- <file>..." to discard changes in working directory)

    modified:   Makefile
    modified:   README.md

no changes added to commit (use "git add" and/or "git commit -a")
```

Update git status:
```sh
$ git add student_info.ini README.md
$ git status
Your branch is up to date with 'origin/master'.

Changes to be committed:
    (use "git reset HEAD <file>..." to unstage)

    modified:   student_info.ini
    modified:   README.md
```
Commit to the change:
```sh
$ git commit -m "<Something you can understand this change>"
```
Push repo to Github:
```sh
$ git push
```
