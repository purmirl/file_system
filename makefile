# ���͸� ����
OBJECTDIRECTORY = temp
SOURCEDIRECTORY	= src

################################################################################
# ���� �׸� �� ���� ��� ����
################################################################################
# �⺻������ ���带 ������ ���
CSOURCEFILES = $(wildcard ./$(SOURCEDIRECTORY)/*.c)
CHEADERFILES = $(wildcard ./$(SOURCEDIRECTORY)/*.h)


all: prepare main.exe Dependency

# ���� �������� ���õ� ������ ����
Dependency:
	gcc -MM $(CSOURCEFILES) > Dependency.dep

# ���� Ŀ�� �̹����� ����
main.exe: $(CSOURCEFILES) 
	@echo $(CSOURCEFILES)
	gcc -o main.exe $(CSOURCEFILES) -g

# ������Ʈ ������ ��ġ�� ���͸��� ����
prepare:
	mkdir -p $(OBJECTDIRECTORY)
		
		
# �ҽ� ������ ������ ������ ���� ����	
clean:
	rm -f *.exe


	