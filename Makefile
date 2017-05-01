MODULES=sort

all: $(MODULES)

# Recursive make for the time being
$(MODULES):
	$(MAKE) -C src/$@
	
.PHONY: clean
clean: 
	$(foreach module, $(MODULES), $(MAKE) clean.$(module);)

.PHONY: clean.%
clean.%:
	$(MAKE) -C src/$* clean	
