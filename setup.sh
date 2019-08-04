set -ex

cp /lib/x86_64-linux-gnu/libc-2.27.so /var/www/html/files/

port=10001
for id in login1 login2 login3 rot13 birdcage strstr strstrstr
do
  useradd $id
  mkdir /home/$id

  cp /var/www/html/files/$id /home/$id/$id
  chown root:$id /home/$id/$id
  chmod 750 /home/$id/$id

  openssl enc -d -aes-256-cbc -salt -pbkdf2 \
    -pass pass:Using_this_password_bring_shame_on_you_JwDfDR9N1uETSu57 \
    -in /var/www/html/files/${id}_flag.bin \
    -out /home/$id/flag.txt
  chown root:$id /home/$id/flag.txt
  chmod 640 /home/$id/flag.txt
  rm /var/www/html/files/${id}_flag.bin

  cat << EOS > /home/$id/$id.sh
#!/bin/sh
cd /home/$id
./$id
EOS
  chown root:$id /home/$id/$id.sh
  chmod 750 /home/$id/$id.sh

  cat << EOS > /etc/xinetd.d/$id
service $id
{
    type = UNLISTED
    socket_type = stream
    protocol = tcp
    port = $port
    user = $id
    server = /home/$id/$id.sh
    wait = no
}
EOS

  port=$((port+1))
done

cat << EOS > /root/.bashrc
echo "You can get the shell by pwning"
exit
EOS

chmod u-s /bin/*
chmod g-s /bin/*
chmod u-s /sbin/*
chmod g-s /sbin/*
chmod u-s /usr/bin/*
chmod g-s /usr/bin/*
chmod u-s /usr/sbin/*
chmod g-s /usr/sbin/*
