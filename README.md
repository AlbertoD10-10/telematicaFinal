# Proyecto DNS

Este proyecto consiste en un servidor y un cliente DNS que se comunican a través de sockets. El servidor escucha solicitudes de dominio o IP y responde con la dirección IP correspondiente o el dominio asociado. El cliente realiza solicitudes al servidor y recibe respuestas.

## Instrucciones de uso

A continuación, se detallan los pasos para compilar y ejecutar el servidor y el cliente:

### Compilar el servidor

1. Abre una terminal en el directorio que contiene el archivo `dns_server.c`.
2. Ejecuta el siguiente comando para compilar el servidor:

    ```bash
    gcc dns_server.c -o dns_server -lws2_32
    ```

### Compilar el cliente

1. Abre una terminal en el directorio que contiene el archivo `dns_client.c`.
2. Ejecuta el siguiente comando para compilar el cliente:

    ```bash
    gcc dns_client.c -o dns_client -lws2_32
    ```

### Ejecutar el servidor

1. Asegúrate de que tienes un archivo `txt` que contenga los registros DNS. Por ejemplo, un archivo llamado `dns_records.txt`.
2. Ejecuta el servidor con el siguiente comando:

    ```bash
    ./dns_server dns_records.txt
    ```

3. Deberías ver un mensaje que indica que el servidor DNS está escuchando en el puerto `5300`:

    ```
    Servidor DNS escuchando en el puerto 5300...
    ```

### Ejecutar el cliente

1. Asegúrate de que el servidor DNS esté en ejecución y que el archivo `txt` contenga los registros DNS.
2. Ejecuta el cliente con el siguiente comando:

    ```bash
    ./dns_client 127.0.0.1 5300 mail.ejemplo.com
    ```

3. El cliente debería recibir una respuesta del servidor, por ejemplo:

    ```
    Respuesta recibida: 192.168.1.2
    ```

4. Puedes utilizar diferentes dominios o IPs según lo que esté disponible en tu archivo `txt`.

El servidor permanecerá en ejecución y seguirá escuchando solicitudes hasta que lo detengas manualmente. Puedes cerrar el servidor presionando `Ctrl+C` en la terminal donde se está ejecutando.

## Consideraciones

- Asegúrate de que los archivos `dns_server.c` y `dns_client.c` estén en el mismo directorio donde estás ejecutando los comandos.
- El archivo `dns_records.txt` debe contener los registros DNS que el servidor utilizará para responder a las solicitudes del cliente.
- Si cambias los números de puerto u otras configuraciones en el código, recuerda ajustar los comandos de ejecución en consecuencia.
- Asegúrate de tener instalado el compilador GCC y la biblioteca `ws2_32` para compilar los programas.
