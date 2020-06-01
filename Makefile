CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE_NAMES="mediatek/mt6765 mediatek/m50"

objtree = $(CURDIR)/
MAIN_DT_NAMES := $(subst $\",,$(CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE_NAMES))
ABS_DTB_FILES := $(abspath $(addsuffix .dtb,$(addprefix $(objtree)dts/,$(MAIN_DT_NAMES))))
$(info $(ABS_DTB_FILES))

my_dtbo_id := 0
define mk_dtboimg_cfg
echo $(1) >>$(2);\
echo " id=$(my_dtbo_id)" >>$(2);\
$(eval my_dtbo_id:=$(shell echo $$(($(my_dtbo_id)+1))))
endef

all: dtbs
	make -C libufdt
	./libufdt/mkdtimg cfg_create dtbo.img dtboimg.cfg
	./libufdt/mkdtimg dump dtbo.img

dtbs: $(objtree)/dtboimg.cfg
$(objtree)/dtboimg.cfg:
	rm -f $@
	rm -f $@.tmp
	$(foreach f,$(ABS_DTB_FILES),$(call mk_dtboimg_cfg,$(f),$@.tmp))
	touch $@.tmp
	if ! cmp -s $@.tmp $@; then \
		mv $@.tmp $@; \
	else \
		rm $@.tmp; \
	fi

