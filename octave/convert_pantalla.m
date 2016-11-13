% script para convertir una imagen en valores hexadecimales

A = imread("pantalla.png");
i = 0;
printf("{ \n")
for f=1:240
  for n=0:9
    % obtener el vector de bits
    vector = A(f,1 + n*32:(n+1)*32);
    % calcular el valor del vector de bits
    num = sum(vector.*2.^[length(vector)-1:-1:0]); 
    if (mod(i, 8) == 0)
        printf("     ")
    end
    % imprimir en hexa
    printf("0x%s, ", num2str(num, "%08X"))
    if (mod(i, 8) == 7)
      printf("\n")
    end
    i++;
  end
end
printf("\n};\n")
