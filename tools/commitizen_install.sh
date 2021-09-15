#!/bin/bash

# npm install the modules
sudo npm install -g commitizen cz-conventional-changelog conventional-changelog validate-commit-msg

# add path to local czrc
echo '{ "path": "cz-conventional-changelog" }' > ~/.czrc

