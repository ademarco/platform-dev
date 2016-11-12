#!/bin/bash

sudo cp ~/.phpenv/versions/$(phpenv version-name)/etc/php-fpm.conf.default ~/.phpenv/versions/$(phpenv version-name)/etc/php-fpm.conf
sudo a2enmod rewrite actions fastcgi alias
echo "cgi.fix_pathinfo = 1" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini
~/.phpenv/versions/$(phpenv version-name)/sbin/php-fpm
cat /etc/apache2/sites-available/*
sudo cp -f resources/travis/vhost.conf /etc/apache2/sites-available/default
sudo sed -e "s?PATH?$(pwd)?g" --in-place /etc/apache2/sites-available/default
cat /etc/apache2/sites-available/default
