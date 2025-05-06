CC      = gcc
CFLAGS  = -O2 -std=c99 -Wall -Iheaders
LDFLAGS = -lm

SRC_DIR = src
HDR_DIR = headers

OBJS = main.o init_levels.o setup.o residual.o restriction.o \
       prolongation.o smooth.o vcycle.o

EXP_N0      = 128
EXP_LEVELS  = 5
EXP_NU1     = 3
EXP_NU2     = 3
EXP_TOL     = 1e-7
EXP_MAXCYC  = 100

all: vcycle_solver

vcycle_solver: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: $(SRC_DIR)/%.c \
	$(HDR_DIR)/init_levels.h \
	$(HDR_DIR)/setup.h \
	$(HDR_DIR)/residual.h \
	$(HDR_DIR)/restriction.h \
	$(HDR_DIR)/prolongation.h \
	$(HDR_DIR)/smooth.h \
	$(HDR_DIR)/vcycle.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: exp1
exp1: vcycle_solver
	@echo "Running Experiment 1: N=$(EXP_N0), levels 2..6"
	@for L in 2 3 4 5 6; do \
	echo "--> levels=$$L"; \
	./vcycle_solver $(EXP_N0) $$L $(EXP_NU1) $(EXP_NU2) $(EXP_TOL) $(EXP_MAXCYC) > out_l$$L.txt; \
	mv residuals.txt res_l$$L.dat; \
	done
	@echo "Experiment 1 done."

.PHONY: exp2
exp2: vcycle_solver
	@echo "Running Experiment 2: grid scaling"
	@for N in 16 32 64 128 256; do \
	echo "--> N=$$N: 2-level"; \
	./vcycle_solver $$N 2 $(EXP_NU1) $(EXP_NU2) $(EXP_TOL) $(EXP_MAXCYC) > out2_$$N.txt; \
	mv residuals.txt res2_$$N.dat; \
	L=1; M=$$N; \
	while [ $$M -gt 8 ]; do M=$$((M/2)); L=$$((L+1)); done; \
	echo "--> N=$$N: full hierarchy (levels=$$L)"; \
	./vcycle_solver $$N $$L $(EXP_NU1) $(EXP_NU2) $(EXP_TOL) $(EXP_MAXCYC) > outmax_$$N.txt; \
	mv residuals.txt resmax_$$N.dat; \
	done
	@echo "Experiment 2 done."

.PHONY: clean
clean:
	rm -f $(OBJS) vcycle_solver *.txt *.dat
