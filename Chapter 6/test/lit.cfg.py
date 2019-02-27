# -*- Python -*-

# Configuration file for the 'lit' test runner.

import lit.formats
from lit.llvm import llvm_config
from lit.llvm.subst import ToolSubst

# name: The name of this test suite.
config.name = 'Chapter 6 example'

# suffixes: A list of file extensions to treat as test files. This is overriden
# by individual lit.local.cfg files in the test subdirectories.
config.suffixes = ['.ll']

# testFormat: The test format to use to interpret tests.
config.test_format = lit.formats.ShTest()

# test_source_root: The root path where tests are located.
config.test_source_root = os.path.dirname(__file__)

# test_exec_root: The root path where tests should be run.
config.test_exec_root = os.path.join(config.ch6_build_path, 'test')

# Tweak the PATH to include the tools dir.
llvm_config.with_environment('PATH', config.llvm_tools_dir, append_path=True)

# Define common LLVM substitutions, such as 'FileCheck' and 'not'.
llvm_config.use_default_substitutions()

# Define substitutions that are specific to the external project.
tools = [ToolSubst('ch6_read_ir', unresolved='fatal')]
llvm_config.add_tool_substitutions(tools, [config.ch6_build_path])
