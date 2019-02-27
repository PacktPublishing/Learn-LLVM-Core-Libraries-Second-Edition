;RUN: llvm-as %s -o %t.bc
;RUN: ch6_read_ir %t.bc | FileCheck %s

;CHECK: foo has 2 basic block(s).
define void @foo() {
entry:
  br label %bb0
bb0:
  ret void
}
