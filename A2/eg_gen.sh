if [[ ! -d $1 ]]
then
mkdir $1
fi
for ((i=1;i<=$2;++i))
do
python3 eg_gen.py > $1/in$i.txt
done