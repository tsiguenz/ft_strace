#!/usr/bin/python3

import requests
import sys
from signal import signal, SIGPIPE, SIG_DFL


FORMAT_TRANSFORM = {
    # every types not here are defined as %lx
    'int':              '%d',
    'size_t':           '%d',
    'off_t':            '%d',
    'pid_t':            '%d',
    'loff_t':           '%d',
    'umode_t':          '%d',
    'rwf_t':            '%d',
    'gid_t':            '%d',
    'uid_t':            '%d',
    'char':             '%c',
    'unsigned':         '0x%lx',
}


# TODO: need to implement this
def add_backslash_to_end(string):
    nbOfSpaces = 80 - len(string)
    string += ' ' * (nbOfSpaces - 1)
    string += '\\'
    return string


def transform_arg(arg):
    if arg.count('*') >= 2:
        return '%p'
    if 'char' in arg and '*' in arg:
        return '\\"%s\\"'
    if '*' in arg:
        return '%p'
    arg = list(arg.split(' '))
    for word in arg:
        if word in list(FORMAT_TRANSFORM.keys()):
            return FORMAT_TRANSFORM[word]
    if '?' not in arg:
        return '0x%lx'
    return ' '.join(arg)


def get_fString(s):
    nr = s['nr']
    name = s['name']
    argumentsList = [s['arg0'], s['arg1'], s['arg2'],
                     s['arg3'], s['arg4'], s['arg5']]
    argumentsList = [transform_arg(arg) for arg in argumentsList if arg]
    fString = f'[{nr}] = {{ "{name}", "%s('
    fString += ', '.join(map(str, argumentsList))
    fString += '" },'
    fString = add_backslash_to_end(fString)
    return fString


def get_sorted_syscall_list(arch):
    url = f'https://api.syscall.sh/v1/syscalls/{arch}'
    response = requests.get(url)
    # code response is always 200
    if len(response.text) <= 3:
        print(f'Error, bad request at url: {url}')
        exit(1)
    responseJson = response.json()
    return sorted(responseJson, key=lambda d: d['nr'])


def get_arch_from_argv():
    try:
        arch = sys.argv[1]
    except Exception:
        print(f'Usage: {sys.argv[0]} ARCH (x64 or x86)')
        exit(1)
    return arch


if __name__ == '__main__':
    # to pipe python output
    signal(SIGPIPE, SIG_DFL)
    arch = get_arch_from_argv()
    syscallList = get_sorted_syscall_list(arch)
    for syscall in syscallList:
        fString = get_fString(syscall)
        print(fString)
