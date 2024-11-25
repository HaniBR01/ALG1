.data
##### R1 START MODIFIQUE AQUI START #####
#
# Este espaço é para você definir as suas constantes e vetores auxiliares.
#
vetor: .word 1 2 3 4 5 6 7 8 9 10
##### R1 END MODIFIQUE AQUI END #####
.text
add s0, zero, zero #Quantidade de testes em que seu programa passou
addi a0, zero, 10
addi a1, zero, 2
jal ra, mmc
addi t0, zero, 10
bne a0,t0,teste2
addi s0,s0,1
teste2: addi a0, zero, 11
addi a1, zero, 7
jal ra, mmc
addi t0, zero, 77
bne a0,t0,teste3
addi s0,s0,1
teste3: addi a0, zero, 6
addi a1, zero, 4
jal ra, mmc
addi t0, zero, 12
bne a0,t0, FIM
addi s0,s0,1
beq zero,zero,FIM
##### R2 START MODIFIQUE AQUI START #####
mmc:
    # Entrada: a0 = número 1, a1 = número 2
    # Saída: a0 = MMC
    # Salva os registradores usados na pilha
    addi sp, sp, -12        # Cria espaço na pilha
    sw ra, 8(sp)            # Salva o registrador de retorno
    sw t0, 4(sp)            # Salva t0
    sw t1, 0(sp)            # Salva t1
    # Inicializa temp0 e temp1
    add t0, a0, zero               # t0 <- a0 (temp0)
    add t1, a1, zero               # t1 <- a1 (temp1)
mmc_loop:
    beq t0, t1, mmc_done	# Enquanto temp0 != temp1
    # Se temp0 > temp1, incrementa temp1
    bgt t0, t1, mmc_incr_temp1
    # Caso contrário, temp1 > temp0, incrementa temp0
    add t0, t0, a0          # temp0 += a0
    j mmc_loop              # Continua o loop
mmc_incr_temp1:
    add t1, t1, a1          # temp1 += a1
    j mmc_loop              # Continua o loop
mmc_done:
    add a0, t0, zero        # MMC encontrado (temp0 ou temp1)
    # Restaura os registradores e retorna
    lw ra, 8(sp)            # Restaura o registrador de retorno
    lw t0, 4(sp)            # Restaura t0
    lw t1, 0(sp)            # Restaura t1
    addi sp, sp, 12         # Limpa espaço na pilha
    jalr zero, 0(ra)        # Retorna
##### R2 END MODIFIQUE AQUI END #####
FIM: addi t0, s0, 0