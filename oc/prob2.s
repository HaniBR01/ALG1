.data
##### R1 START MODIFIQUE AQUI START #####
#
# Este espaço é para você definir as suas constantes e vetores auxiliares.
#
vetor1: .word 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 #Primeiro vetor
##### R1 END MODIFIQUE AQUI END #####
.text

add s0, zero, zero
# a2 é definido como constante, e ele é esperado na chamada de funções
# a1 é definido como endereço do vetor, e ele é esperado na chamada de funções
# a0 é o parametro do eprimo 
la a1, vetor1		
addi t0, zero, 16   # Deslocamento para o 5º elemento (4 * 4 bytes)
add t1, a1, t0      # Soma o deslocamento ao endereço base (t1 = endereço do 4º elemento)
lw a0, 0(t1)        # Carrega o valor do 4º elemento no registrador a0

jal ra, eprimo

add t0, zero, zero
bne a0,t0,teste2
addi s0,s0,1
teste2:
    addi a2, zero, 2
    jal ra, primosmersenne
    addi t0, zero, 7
    bne a2,t0, FIM
    addi s0,s0,1
   	beq zero,zero, FIM
    
##### R2 START MODIFIQUE AQUI START #####
# Esse espaço é para você escrever o código dos procedimentos.
# Por enquanto eles estão vazios

geramersenne:
    # Salva os registradores necessários na pilha
    addi sp, sp, -24        # Reserva espaço na pilha
    sw ra, 0(sp)            # Salva o registrador ra
    sw t0, 4(sp)            # Salva t0 (contador)
    sw t1, 8(sp)            # Salva t1 (indice do vetor)
    sw t2, 12(sp)           # Salva t2 (shift de mersenne)
    sw t3, 16(sp)           # Salva t3 (numero mersenne)
    sw t4, 20(sp)           # Salva t4 (limite do vetor)

    # Inicialização
    add t0, zero, zero      # t0 = contador = 0 (índice atual)
    add t1, a1, zero        # t1 = endereço atual no vetor
    addi t4, zero, 32		# t4 = 32 tamanho do vetor

geramersenne_loop:
    bge t0, t4, geramersenne_done  # Se contador >= quantidade, sai do loop
    # Calcula 2^(t0+1) - 1
    add t2, t0, zero          # t2 = n = t0 + 1
    addi t3, zero, 1        # t3 = base = 1 (2^0)

geramersenne_pow:
    beqz t2, geramersenne_store # Se t2 == 0, vai armazenar
    slli t3, t3, 1          # t3 = t3 * 2
    addi t2, t2, -1         # Decrementa t2
    j geramersenne_pow

geramersenne_store:
    addi t3, t3, -1         # t3 = t3 - 1 (2^n - 1)
    sw t3, 0(t1)            # Armazena t3 no vetor
    addi t1, t1, 4          # Incrementa o endereço do vetor
    addi t0, t0, 1          # Incrementa o contador
    j geramersenne_loop     # Próximo número

geramersenne_done:
    # Restaura os registradores e retorna
    lw ra, 0(sp)            # Restaura o registrador ra
    lw t0, 4(sp)            # Restaura t0
    lw t1, 8(sp)            # Restaura t1
    lw t2, 12(sp)			# Restaura t2
    lw t3, 16(sp)			# Restaura t3
    lw t4, 20(sp)			# Restaura t4
    addi sp, sp, 24         # Libera espaço na pilha
    jalr zero, 0(ra)        # Retorna             # t3 = base = 1 (2^0

eprimo:
	addi sp, sp, -12
    sw t0, 8(sp)
    sw t1, 4(sp)
    sw ra, 0(sp)
    addi t0, zero, 2
    bgt t0, a0, not_primo
    addi t0, zero, 4
    bgt t0, a0, primo
    addi t0, zero, 1
	loop:
    	addi t0, t0, 1
        rem t1, a0, t0
        beq t1, zero, not_primo
        mul t1, t0, t0
        bgt a0, t1, loop
    primo:
    	add a0, zero, zero
        lw t0, 8(sp)
        lw t1, 4(sp)
        lw ra, 0(sp)
 		addi sp, sp, 12
		jalr zero, 0(ra)
    not_primo:
    	addi a0, zero, 1
        lw t0, 8(sp)
        lw t1, 4(sp)
        lw ra, 0(sp)
 		addi sp, sp, 12
		jalr zero, 0(ra)
        
primosmersenne:
	addi sp, sp, -12
    sw t0, 8(sp)
    sw t1, 4(sp)
    sw ra, 0(sp)
	jal ra, geramersenne
    
	jalr zero, 0(ra)

##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0