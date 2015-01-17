import sys

input_data = open('/tmp/indb.txt').read().split("\n")
functions = []
headers = """#include </usr/include/python2.7/Python.h>
#include "pin.H"
#include "INS.h"
"""

for line in input_data:
    if not line or line[0] == '#' or 'PIN_' in line:
        continue
    line = line.replace(' *','').replace("LEVEL_CORE::", "").replace("const ", "").replace("LEVEL_PINCLIENT::","").replace('&', '').split()
    args = line[2:]#.join(' ').replace('(','').replace(')','')
    args = ' '.join(args).replace('(','').replace(')','').split(', ')
    return_type = line[0]
    function_name = line[1]
    function = {}
    function['return_type'] = return_type
    function['name'] = function_name
    function['args'] = []
    for arg in args:
        if not arg:
            continue
        try:
            function['args'].append({'type':arg.split()[0], 'name':arg.split()[1]})
        except IndexError:
            print line
            sys.exit(1)

    functions.append(function)

skeleton = \
"""PyObject* Python_%name%(PyObject* self, PyObject* args) {
%decls%
%parsetuple%


%body%
}
"""

unknowns = []
buffer = ""
for function in functions:
    decls = ""
    parsetuple = ""
    body = ""

    types = []
    args = ', '.join('&%s'%arg['name'].lower() for arg in function['args'])

    for arg in function['args']:
        decls += "    PyObject* %s;\n" % (arg['name'].lower())
        if arg['type'] in ['int', 'UINT16', 'INT32', 'USIZE', 'UINT32', 'INS', 'REG', 'ADDRDELTA']:
            types.append('L')
            body += "    %s %s_object = *(%s*) %s;\n" % (arg['type'], arg['name'].lower(), arg['type'], arg['name'].lower())
        elif arg['type'] in ['BOOL']:
            types.append('O')
        else:
            print "%s is unknown"%(arg['type'])
            sys.exit(1)
            break

    if function['return_type'] == 'BOOL':
        body += \
"""
    if (%s(%s)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }""" % (
            function['name'],
            ', '.join([arg['name'].lower()+'_object' for arg in function['args']])
        )
    elif function['return_type'] == 'string':
        body += '\n    return Py_BuildValue("s", %s(%s).c_str());' % (
            function['name'],
            ', '.join([arg['name'].lower()+'_object' for arg in function['args']])
        )
    elif function['return_type'] in ['RTN', 'REG', 'OPCODE', 'INS']:
        body += "\n    %s* %s_return = (%s*) malloc(sizeof(%s));" % (
            function['return_type'],
            function['return_type'].lower(),
            function['return_type'],
            function['return_type']
        )
        body += '\n    *%s_return = %s(%s);' % (
            function['return_type'].lower(),
            function['name'],
            ', '.join([arg['name'].lower()+'_object' for arg in function['args']])
        )
        body += '\n    return Py_BuildValue("L", %s_return);' % (function['return_type'].lower())
    elif function['return_type'] in ['INT32', 'USIZE', 'PREDICATE', 'UINT32', 'SYSCALL_STANDARD', 'ADDRINT', 'ADDRDELTA', 'UINT64']:
        body += '    return Py_BuildValue("L", %s(%s));' % (
            function['name'],
            ', '.join([arg['name'].lower()+'_object' for arg in function['args']])
        )
    else:
        unknowns.append(function['name'])
        print function['return_type'], function['name']
        continue

    parsetuple = '    PyArg_ParseTuple(args, "%s", %s);' % ('|'.join(types), args)

    buffer += skeleton.replace('%name%', function['name']).replace('%decls%', decls).replace('%parsetuple%', parsetuple).replace('%body%', body).replace("\n\n", "\n")
    buffer += "\n"

print headers
print buffer

if unknowns:
    print unknowns
