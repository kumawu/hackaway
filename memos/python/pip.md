# install package into .local 
make sure there is a .pip directory exist!
if not
```
mkdir .pip
```

then 
```
cd .pip & touch pip.conf
```

and add the following content 
```
[install]
install-option=--prefix=~/.local

```
