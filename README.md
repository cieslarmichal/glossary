[![Build Status](https://travis-ci.org/michalovsky/glossary.svg?branch=master)](https://travis-ci.org//michalovsky/glossary)

[![Build status](https://ci.appveyor.com/api/projects/status/qknnoy8h9u5stvyt/branch/master?svg=true)](https://ci.appveyor.com/project/michalovsky/glossary/branch/master)
[![codecov](https://codecov.io/gh/michalovsky/glossary/branch/master/graph/badge.svg)](https://codecov.io/gh/michalovsky/glossary)
[![CodeFactor](https://www.codefactor.io/repository/github/michalovsky/glossary/badge)](https://www.codefactor.io/repository/github/michalovsky/glossary)

# Glossary

<h3>1. Requirements:</h3>
<ul>
  <li>compiler that supports C++ 17</li>
  <li>git</li>
  <li>cmake</li>
  <li>boost</li>
  <li>Qt 5.12 (at least)</li>
</ul>

<h3>2. Get api keys:</h3>
<ul>
  <li>Google Translate api key: 
    https://neliosoftware.com/blog/how-to-generate-an-api-key-for-google-translate/
  </li> 
  <li>Words api key:
  https://rapidapi.com/dpventures/api/wordsapi/pricing
  </li>
</ul>

<h3>3. Downloading and compiling code:</h3>

    git clone https://github.com/michalovsky/glossary.git

    git submodule update --init --recursive

    cd glossary
    mkdir build-linux
    cd build-linux
    cmake ..
    make
    
<h3>4. Run application: </h3>
    In build-linux directory:

    src/gui/gui


<h3>5. Running UTs for linux:</h3>

    cd glossary
    ./runUT_linux.sh



