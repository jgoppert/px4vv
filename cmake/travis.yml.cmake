language: c

before_install:
    sudo apt-get update

install:
    sudo apt-get install cmake clang

script:
    mkdir -p build && cd build && cmake .. && make && ctest -V

#after_success:

#after_failure:

#after_script:

#before_deploy:
    #cd build && cpack

#deploy:

#after_deploy:
#


env:
  global:
    # COVERITY_SCAN_TOKEN
    # ** specific to your project **
    - secure: eTJb8rC-LAR7qggJzv-7jA
addons:
  coverity_scan:

    # GitHub project metadata
    # ** specific to your project **
    project:
      name: jgoppert/px4vv
      version: @VERSION_MAJOR@.@VERSION_MINOR@.@VERSION_PATCH@
      description: PX4 + Model Checking

    # Where email notification of build analysis results will be sent
    notification_email: james.goppert@gmail.com

    # Commands to prepare for build_command
    # ** likely specific to your build **
    build_command_prepend: cmake .

    # The command that will be added as an argument to "cov-build" to compile your project for analysis,
    # ** likely specific to your build **
    build_command: make

    # Pattern to match selecting branches that will run analysis. We recommend leaving this set to 'coverity_scan'.
    # Take care in resource usage, and consider the build frequency allowances per
    #   https://scan.coverity.com/faq#frequency
    branch_pattern: coverity_scan

# vim: set et fenc= ff=unix sts=0 sw=2 ts=2 :
