.PHONY: clean All

All:
	@echo "----------Building project:[ SkylineProblem - Debug ]----------"
	@cd "SkylineProblem" && $(MAKE) -f  "SkylineProblem.mk"
clean:
	@echo "----------Cleaning project:[ SkylineProblem - Debug ]----------"
	@cd "SkylineProblem" && $(MAKE) -f  "SkylineProblem.mk" clean
