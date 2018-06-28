ASM_PATH = asm_dir/
VM_PATH = vm_dir/
ASM_NAME = asm
VM_NAME = corewar

.PHONY: all, clean, fclean, re, norme

all:
	make -C $(ASM_PATH)
	make -C $(VM_PATH)
	cp $(ASM_PATH)asm/$(ASM_NAME) .
	cp $(VM_PATH)$(VM_NAME) .

clean:
	make clean -C $(ASM_PATH)
	make clean -C $(VM_PATH)
	rm -f $(ASM_NAME)
	rm -f $(ASM_NAME)

fclean: clean
	make fclean -C $(ASM_PATH)
	make fclean -C $(VM_PATH)

re: fclean all
