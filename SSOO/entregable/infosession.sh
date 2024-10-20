#!/bin/bash

show_sidzero=0
show_help=0

while [ -n "$1" ]; do
  case $1 in
    -h)
      show_help=1
      ;;
    -z)
      show_sidzero=1
      ;;
    -u)
      shift
      if [[ $1 == -* ]]; then
        echo "A la opcioón -u le falta un argumento"
        exit 1
      fi
      user=$1
      ;;
    *)
      echo "ERROR. Opción desconocida: '$1'"
      exit 1
  esac
done

if [ show_help=1 ]; then
  echo "ayuda"
  exit 0
fi

processes=$(get_processes)
if [ $show_sidzero=0] ; then
  processes=$(filter_sidzero "processes")
fi

if [ -n $user ]; then
  processes=$(filter_by_user "$processes" "$user")
fi

