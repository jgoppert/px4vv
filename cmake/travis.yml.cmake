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
   # The next declaration is the encrypted COVERITY_SCAN_TOKEN, created
   #   via the "travis encrypt" command using the project repo's public key
   - secure: "Gq7Mz/H4fsBYq6cDf3dGJnW4UKvNB6FHUFnqm/iQs/fNjLnum/HOlsZiw9triBNVHxmtMN2hpGoHCybLFUkSgnBL5peIj+grp2JT937rKxfKdiOgHOaTU2YjfQHuAphdjVfNUU9r+K/20Ecjgrafy1QrhASFmOIUfSw0QE+8ilJm3IazZmK4nN4FotLg44nJpN7coF7D5styrBFGCpCsrFHXHo2I8B75jDUnJ3D29TSwWZrZTh5PzTAOoNi9B3BLOCdSlUMI0PjKAGm0epGKprVh4inQhh2sIWox21CzLZLGTAKVy+496d0Trm4g4QyndN5U4sYFqFdAM+YOAvXWw5JoH5WxM9L5F/grMNQ6WmwTkdFGuPmLTCwLOw72Bfy9qpoOD9LksbUBJ2l0omxAqZ+Sqk4tKH/Qhe/cyKd2Hx2F6DrVJ4T6p/AxY0epAB+AtEgmrmh8u4Sx/pAC/sMF1yztksvgnJ8WAATxBFTvucI4mKQJnadxJKg/kopnZ2GmCEVS2clewz1ys1FAMauRSv85Dy0idQ+Gnk+46TWi0uUG8CU/ezRr4YjQB+AY4TaHaODh6X3NMkGiIf3BeZzqFUo1nq26Zc2Hn+H993m/ZVygyRNjoWEsgobHIQr7eGXxh7iQHOS5C97NtQeDyXZKH2VbyfIKe5lY2r6NYlL2qAE="

addons:
  coverity_scan:
    project:
      name: "jgoppert/px4vv"
      description: "Build submitted via Travis CI"
    notification_email: james.goppert@gmail.com
    build_command_prepend: "mkdir -p build && cd build && cmake .. && make"
    build_command:   "make -C build -j 4"
    branch_pattern: coverity_scan

# vim: set et fenc= ff=unix sts=0 sw=2 ts=2 :
