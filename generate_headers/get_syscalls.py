#!/usr/bin/python3

import requests
import sys
from signal import signal, SIGPIPE, SIG_DFL


def add_backslash_to_end(string):
    print(string)


def delete_arg_name(arg):
    arg = list(arg.split(' '))
    if len(arg) > 1:
        arg.pop(-1)
    arg = ' '.join(arg)
    return arg


def get_fString(s):
    nr = s['nr']
    name = s['name']
    argumentsList = (s['arg0'], s['arg1'], s['arg2'],
                     s['arg3'], s['arg4'], s['arg5'])
    argumentsList = [arg for arg in argumentsList if arg]
    argumentsList = [delete_arg_name(arg) for arg in argumentsList]
    print(argumentsList)
    fString = f'[{nr}] = {{ "{name}", "%s('
    fString += ', '.join(map(str, argumentsList))
    return fString


def get_sorted_syscall_list(arch):
    url = f'https://api.syscall.sh/v1/syscalls/{arch}'
    response = requests.get(url)
    if response.status_code != 200:
        print(f"Error, bad request at url: {url}")
        exit(1)
    responseJson = response.json()
    return sorted(responseJson, key=lambda d: d['nr'])


def get_arch_from_argv():
    try:
        arch = sys.argv[1]
    except Exception:
        print(f"Usage: {sys.argv[0]} ARCH (x64 or x86)")
        exit(1)
    return arch


if __name__ == '__main__':
    # to pipe python output
    signal(SIGPIPE, SIG_DFL)
    arch = get_arch_from_argv()
    syscallList = get_sorted_syscall_list(arch)
    for syscall in syscallList:
        fString = get_fString(syscall)
        # print(fString)
