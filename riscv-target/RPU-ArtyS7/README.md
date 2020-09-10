ArtyS7-RPU-SoC Target

This simply builds the tests into .elf files which can be loaded and then jumped into. Context is saved and restored on exit. When the test is complete, RET is executed which should return back into a test harness, which can then pull out the test signature results to compare against golden values.

Useful for running on hardware which already has .elf loader facilitites

Use:
make RISCV_TARGET=RPU-ArtyS7 RISCV_DEVICE=rv32i

Supported Devices: rv32i rv32im rv32Zicsr rv32Zifencei