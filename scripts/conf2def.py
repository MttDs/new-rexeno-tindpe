#! /usr/bin/python

import re

f = open('conf')
lines = f.readlines()

res=""
sep=" "
for line in lines:
    if re.compile('id[0-9]').search(line):
        words = line.split()
        words[0] = '>'
        res = res + sep.join(words) + '\n'
        continue
    if re.compile('idtrial').search(line):
        words = line.split()
        words[0] = '|'
        res = res + sep.join(words) + '\n'
        continue
    if re.compile('endtrial').search(line):
        words = line.split()
        words[0] = ';'
        res = res + sep.join(words) + '\n'
        continue
    if re.compile('^end$').search(line):
        words = line.split()
        words[0] = ''
        res = res + sep.join(words) + '\n'
        continue

print res
