% Script de Octave para leer y graficar datos desde el puerto serial.

serial_init

% creamos una figura
clf
clear t v
t(1) = 0; v(1) = 0;
h = plot(t, v, '.');
grid on

srl_write(fd, "c"); % iniciar captura
unwind_protect
  while(1)
    n = a_numero(srl_read(fd, 10));
    i = n + 1;
    t(i) = n * Tm;
    srl_read(fd, 2); % descartar ', '
    n = a_numero(srl_read(fd, 4));
    v(i) = n * LSB;
    srl_read(fd, 2); % descartar '\r\n'
    if (mod(i, 100) == 0)
      % actualizar gráfico
      set(h, 'XData', t, 'YData', v);
      drawnow;
    end
  end
unwind_protect_cleanup
  % Ctrl-C, detener y cerrar la conección
  srl_write(fd, "c");
  fclose(fd);
  % guardar los datos capturados
  if (length(t) != length(v))
    % antes de guardar las longitudes tienen que ser iguales
    N = min([length(t), length(v)]);
    t = t(1:N);
    v = v(1:N);
  end
  csvwrite(sprintf("captura_continua_%s-%s.csv", date, strftime("%H:%M", localtime(time))), [t' v']);
end
