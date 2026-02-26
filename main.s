rfact:
  pushq %rbx
  movq %rdi, %rbx
  mov $1, %eax
  cmp $1, %rdi
  jle .L3
  subq $1, %rdi
  call rfact
  imulq %rbx, %rax
  .L3
  popq %rbx
  ret
