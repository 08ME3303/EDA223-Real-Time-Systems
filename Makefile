.PHONY: clean All

All:
	@echo "----------Building project:[ RTS-Lab - Debug ]----------"
	@cd "orchestra-frederik" && "$(MAKE)" -f  "RTS-Lab.mk" && "$(MAKE)" -f  "RTS-Lab.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ RTS-Lab - Debug ]----------"
	@cd "orchestra-frederik" && "$(MAKE)" -f  "RTS-Lab.mk" clean
