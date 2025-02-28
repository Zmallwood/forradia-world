#!/usr/bin/sh

env_file=".env"

if [ -f "$env_file" ]
then
    export $(cat .env | xargs)
else
    echo "WARNING: Missing $env_file file."
fi

if [ -z "$NGROK_AUTHTOKEN" ]; then
    echo "WARNING: NGROK_AUTHTOKEN is not defined"
fi

envsubst < ngrok.yml.template > ngrok.yml

nohup ngrok start --all --config ./ngrok.yml &
echo "Ngrok started. Client is accessible on: https://$WEB_SERVER_HOST"
rm -rf ./published/*
mkdir -p ./published/build/
cp -r ./develop/build/forradia-world ./published/build/
cp -r ./develop/html/ ./published/
sudo ./published/build/forradia-world
echo "Exiting ngrok..."
pkill ngrok
