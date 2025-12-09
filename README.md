# LHWn - Title

_A quick blurb or sub-title text_

## Background

Before proceeding with this lab, the student should take the time to read

* this
* that
* and the other thing

## Objective

Upon successful completion of this lab, the student has learned how to

* do this
* do that
* do another thing

## Getting Started

After accepting this assignment with the
provided GitHub Classroom Assignment link, decide how you want to work with
your newly created repository:

* Using Codespaces directly in your web browser that employees the Visual Studio Code online IDE, or
* Using the IDE of your choice on your local machine

### ⚙️ Setup

Included in this repository is a script named [`setup.sh`](./setup.sh) that installs all the tools used by the GitHub actions that ultimately grade your assignment and that can be utilized by an IDE to help write code using modern styles and practices. This script is intended to run in a Debian distribution of Linux (e.g., Ubuntu). Our codespaces run Ubuntu, so it is advised you develop in a codespace.

To run this script (and it should be the first thing you do), simply open a terminal window and type:

```shell
sudo ./setup.sh
```

This script might take a minute or two to complete. You will also find a manual decision to make for configuring the `openssh-server`.

```
Configuring openssh-server
--------------------------

A new version (/tmp/tmp.1tzvgwylD9) of configuration file /etc/ssh/sshd_config
is available, but the version installed currently has been locally modified.

  1. install the package maintainer's version
  2. keep the local version currently installed <-- choose this option
  3. show the differences between the versions
  4. show a side-by-side difference between the versions
  5. show a 3-way difference between available versions
  6. do a 3-way merge between available versions
  7. start a new shell to examine the situation
What do you want to do about modified configuration file sshd_config?
```

Depending on your terminal window and font sizes, you may not see all the options immediately (in which case you'll see `[More]` -- just hit the space bar until you see the prompt question). Select option **2** to `keep the local version currently installed`.

You'll see the following message when the script completes successfully:

```
All specified packages have been installed successfully.
```

and you'll be back at the command line prompt.

### Codespaces

If a Codespace is available for use (and this is your preferred method of development), open your newly created
repository in a Codespace.

At this point, you can skip to [Creating a development branch](#creating-a-development-branch).

### Local Development

Depending upon the IDE of your choice, many of the following steps may be taken within your IDE. It is up to you to
discover these tools (assuming they're available) and learn how to use them appropriately as desired. The following
instructions are assumed to take place within a terminal window. Note: many IDEs provide a terminal window as well.

#### Cloning your repository

The command you use to clone is slightly different depending upon whether
you're using `git` via `https`, `ssh`, or using the GitHub Cli via `gh`.

If you're using the `https` protocol, your clone command is:

```shell
git clone https://github.com/msu-csc232-fa25/<repo-name>.git
```

If you're using the `ssh` protocol, your clone command is:

```shell
git clone git@github.com:msu-csc232-fa25/<repo-name>.git
```

Finally, if you're using the GitHub CLI (`gh`), your clone command is:

```shell
gh repo clone msu-csc232-fa25/<repo-name>
```

After cloning the repository, navigate into the newly cloned repository:

```shell
cd <repo-name>
```

#### Creating a development branch

Next, create a branch named `develop`. Please note: The name of this branch **must** be as specified and will be, to the
grading scripts, case-sensitive.

```shell
git checkout -b develop
```

Make sure you are on the `develop` branch before you get started. Make all your commits on the `develop` branch.

```bash
git branch
```

_You may have to type the `q` character to get back to the command line prompt after viewing the status. If this annoys you, it can be configured to not exemplify this behavior. Simply type the following in your terminal window:_

```shell
git config --global pager.branch false
```

#### Manually formatting your files

Here's a linux command you can run from the root folder of your repositories terminal window to automatically reformat your files (if it can) in place:

```shell
find ./include ./src -name '*.h' -o -name '*.hpp' -o -name '*.c' -o -name '*.cpp' | xargs clang-format -i
```

* `find` generates a list of file names that match the file patterns
* `|` is the pipe symbol; it's "piping" the list of file names found by the previous command (`find`)
* `xargs` takes each of these file names piped into it, and supplies it as an argument to the
* `clang-format` command, which is executed in the interactive switch (`-i`) so as to make the changes in place

This is something you should get in the habit of doing to ensure you're getting full points on your style category of your assignments. This command _presumes_ you have run the [`setup.sh`](./setup.sh) script first, which installs the clang-format program. See [Setup](#️-setup).

## Tasks

This assignment consists of the following tasks:

* Task 1: <TODO: Declare me!>
* Task 2: <TODO: Declare me!>
* Task 3: <TODO: Declare me!>
* Task 4: <TODO: Declare me - or erase me!>
* Task 5: <TODO: Declare me - or erase me!>

Pol, neuter abactor!

### Task 1: <TODO: Declare me!>

Ecce, urbs!

### Task 2: <TODO: Declare me!>

Ubi est dexter medicina?

### Task 3: <TODO: Declare me!>

Ubi est dexter medicina?

### Task 4: <TODO: Declare me!>

Ubi est dexter medicina?

### Task 5: <TODO: Declare me!>

Ubi est dexter medicina?

## Submission Details

Before submitting your assignment, be sure you have pushed all your changes to GitHub. If this is the first time you're
pushing your changes, the push command will look like:

```bash
git push -u origin develop
```

If you've already set up remote tracking (using the `-u origin develop` switch), then all you need to do is type

```bash
git push
```

As usual, prior to submitting your assignment on Brightspace, be sure that you have committed and pushed your final
changes to GitHub. Once your final changes have been pushed, create a pull request that seeks to merge the changes in
your `develop` branch into your `main` branch.

You can use `gh` to create this pull request right from your command-line prompt:

```bash
gh pr create --assignee "@me" --title "Some appropriate title" --body "A message to populate description, e.g., Go Bills!" --head develop --base main --reviewer msu-csc232-fa25/graders
```

An "appropriate" title is at a minimum, the name of the assignment, e.g., `LAB02` or `HW04`, etc.

Once your pull request has been created, submit the URL of your assignment _repository_ (i.e., _not_ the URL of the pull
request) as a Text Submission on Brightspace. Please note: the timestamp of the submission on Brightspace is used to
assess any late penalties if and when warranted, _not_ the date/time you create your pull request. **No exceptions will
be granted for this oversight**.

### Due Date

Your assignment submission is due by ...

### Grading Rubric

This assignment is worth **3|5 points**.

| Criteria           | Exceeds Expectations         | Meets Expectations                  | Below Expectations                  | Failure                                        |
|--------------------|------------------------------|-------------------------------------|-------------------------------------|------------------------------------------------|
| Pull Request (20%) | Submitted early, correct url | Submitted on-time; correct url      | Incorrect URL                       | No pull request was created or submitted       |
| Code Style (20%)   | Exemplary code style         | Consistent, modern coding style     | Inconsistent coding style           | No style whatsoever or no code changes present |
| Correctness^ (60%) | All unit tests pass          | At least 80% of the unit tests pass | At least 60% of the unit tests pass | Less than 50% of the unit tests pass           |

^ _The Google Test unit runner will calculate the correctness points based purely on the fraction of tests passed_.

### Late Penalty

* In the first 24-hour period following the due date, this assignment will be penalized 20%.
* In the second 24-hour period following the due date, this assignment will be penalized 40%.
* After 48 hours, the assignment will not be graded and thus earns no points.

## Disclaimer & Fair Use Statement

This repository may contain copyrighted material, the use of which may not
have been specifically authorized by the copyright owner. This material is
available in an effort to explain issues relevant to the course or to
illustrate the use and benefits of an educational tool. The material
contained in this repository is distributed without profit for research and
educational purposes. Only small portions of the original work are being
used and those could not be used to easily duplicate the original work.
