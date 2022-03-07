#!/bin/zsh

emulate -R sh

cd $(dirname $0)

for i in `seq 1 1000`
do
#echo 'bsub -q s -u ushizawa@post.kek.jp -o seed_${i}_ang30_mup_Al.out -N `./Acceptance_calculation $i settingAl_mu_2 run.mac 1>/dev/null`'
bsub -q s -u ushizawa@post.kek.jp -o seed_${i}_ang30_mup_Al.out -N "./Acceptance_calculation $i settingAl_mu_2 run.mac 1>/dev/null"
done
