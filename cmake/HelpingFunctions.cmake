# set of functions to make my orignal Cmakefile less bloated

function(check_if_file_exist THE_FILE)
    if(NOT EXISTS THE_FILE)
        message(WARNING "${THE_FILE} does not exist")
    else()
        message(STATUS "${THE_FILE} does exist")
endfunction()
