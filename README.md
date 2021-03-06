[![Build Status](https://status.continuousphp.com/git-hub/ec-europa/platform-dev?token=4df2e996-5362-486e-b409-84527de6a65b&branch=develop)](https://continuousphp.com/git-hub/ec-europa/platform-dev)

# NextEuropa

## Requirements

* Composer
* PHP Phar extension
* PhantomJS (in order to run JavaScript during Behat tests)

## Install build system

Before we can build the NextEuropa platform we need to install the build system
itself. This can be done using composer:

```
$ composer install
```

### Tips

If you have a global install of composer already, this may cause conflict.
Try the command below.

```
$ curl -sS https://getcomposer.org/installer | php
```

## Customize build properties

Create a new file in the root of the project named `build.properties.local`
using your favourite text editor:

```
$ vim build.properties.local
```

This file will contain configuration which is unique to your development
machine. This is mainly useful for specifying your database credentials and the
username and password of the Drupal admin user so they can be used during the
installation.

Because these settings are personal they should not be shared with the rest of
the team. Make sure you never commit this file!

All options you can use can be found in the `build.properties.dist` file. Just
copy the lines you want to override and change their values. For example:

```
# The location of the Composer binary.
composer.bin = /usr/bin/composer

# The install profile to use.
platform.profile.name = multisite_drupal_standard

# Database settings.
drupal.db.name = my_database
drupal.db.user = root
drupal.db.password = hunter2

# Admin user.
drupal.admin.username = admin
drupal.admin.password = admin

# The base URL to use in Behat tests.
behat.base_url = http://nexteuropa.local
```

## Listing the available build commands

You can get a list of all the available Phing build commands ("targets") with a
short description of each target with the following command:

```
$ ./bin/phing
```

## Building a local development environment

```
$ ./bin/phing build-platform-dev
$ ./bin/phing install-platform
```

## Running Behat tests

The Behat test suite is located in the `tests/` folder. When the development
version is installed (by running `./bin/phing build-platform-dev`) the Behat
configuration files (`behat*.yml`) will be generated automatically using the
base URL that is defined in `build.properties.local`.

If you are not using the development build but one of the other builds
(`build-platform-dist` or `build-multisite-dist`) and you want to run the tests
then you'll need to set up the Behat configuration manually:

```
$ ./bin/phing setup-behat
```

In order to run JavaScript in your Behat tests, you must launch a PhantomJS
instance before. Use the `--debug` parameter to get more information. Please
be sure that the webdriver's port you specify corresponds to the one in your
Behat configuration (`wd_host: "http://localhost:8643/wd/hub"`).

```
$ phantomjs --debug=true --webdriver=8643
```

The tests can also be run from the root of the repository (or any other folder)
by calling the behat executable directly and specifying the location of the
`behat*.yml` configuration file.

The tests can be executed from the root folder of the build:

```
$ cd build/
$ ../bin/behat -c tests/behat.yml
```

With a single Phing task, you can run every tests suites:

```
./bin/phing behat
```

If you want to run only one specific tests suite (defined in its own
configuration file), you can specifiy it as a parameter:

```
# Running the tests from the repository root folder.
$ ./bin/behat -c tests/behat.yml
```

If you want to execute a single test, just provide the path to the test as an
argument. The tests are located in `tests/features/`. For example:

```
$ ./bin/behat -c tests/behat.api.yml tests/features/content_editing.feature
```

Some tests need to mimic external services that listen on particular ports, e.g.
the central server of the Integration Layer. If you already have services running
on the same ports, they will conflict. You will need to change the ports used in
build.properties.local.

Remember to specify the right configuration file before running the tests.

## Checking for coding standards violations

When a development build is created by executing the 'build-platform-dev' Phing
target PHP CodeSniffer will be set up and can be run with the following
command:

```
# Scan all files for coding standards violations.
$ ./bin/phpcs

# Scan only a single folder.
$ ./bin/phpcs profiles/common/modules/custom/ecas
```
