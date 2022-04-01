# SocketProgramming
TCP protokolü ve IPv4 adresleme ile local ağda Soket iletişimi. Socket communication via TCP and IPv4 in LAN

Kullanılan bazı metotların kaynağı: https://man7.org/linux/man-pages/index.html


Server kodumuzu çalıştırken bizden ek olarak bir PortNo istemektedir, bu iletişim kurmak için açmak istediğimiz port numarasıdır.
Client kodumuzu çalıştırken de bizden ek olarak bağlanacağımız IP adress (server kodumuzun çalıştığı cihazın IP adresi) ve bağlanacağımız port numarasını istemektedir. Burda girilen port no'lar aynı olmalıdır. Gerekli usage bilgileri kod içerisinde de kontrol edilip verilmektedir.

