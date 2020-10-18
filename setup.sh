set -ex

cp /lib/x86_64-linux-gnu/libc-2.31.so /var/www/html/files/
cp /lib227/libc-2.27.so /var/www/html/files/
ln -s /lib227/libc-2.27.so /lib227/libc.so.6

# uidの下の桁をポート番号と揃える
useradd user

port=10001
for id in login1 login2 login3 rot13 birdcage strstr227 strstr231 strstrstr freefree freefree++227 freefree++231 writefree shellsort
do
  useradd $id
  mkdir /home/$id

  bin=$(echo $id | sed -r 's/227|231//')

  cp /var/www/html/files/$bin /home/$id/$bin
  chown root:$id /home/$id/$bin
  chmod 750 /home/$id/$bin

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
./$bin
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

for id in birdcage strstr227 strstrstr freefree++227 writefree
do
  bin=$(echo $id | sed -e 's/227//')
  patchelf --set-rpath /lib227/ --set-interpreter /lib227/ld-2.27.so /home/$id/$bin
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
