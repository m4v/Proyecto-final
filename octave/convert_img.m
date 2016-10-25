% script para convertir una imagen en valores hexadecimales

A = imread("8x12_arrow.png");

for n=1:12
  D=A(n,1:8);
  num = sum(D.*2.^[length(D)-1:-1:0]); 
  printf("0x%s", num2str(num, "%04X, "))
end
 


%for n=0:9
%  D = A(:,1 + n*24:(n+1)*24);
%  printf("{{ /* número %d*/\n", n)
%  for i=1:42
%    vector = D(i,:); % vector de bits
%    % calcular el valor del vector de bits
%    num = sum(vector.*2.^[length(vector)-1:-1:0]); 
%    if (mod(i, 7) == 1)
%      printf("     ")
%    end
%    % imprimir en hexa
%    printf("0x%s", num2str(num, "%08X"))
%    if (i < 42)
%      printf(", ")
%    end
%    if (mod(i, 7) == 0)
%      printf("\n")
%    end
%  end
%  printf("\n}},\n")
%end
