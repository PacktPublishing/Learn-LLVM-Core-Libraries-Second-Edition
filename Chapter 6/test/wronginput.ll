;RUN: not ch6_read_ir %s 2> %t.err
;RUN: FileCheck --input-file=%t.err %s
;CHECK: Error while processing the bitcode file
